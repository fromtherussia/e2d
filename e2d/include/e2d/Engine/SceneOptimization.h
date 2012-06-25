#ifndef E2D_ENGINE_SCENE_OPTIMIZATION_H
#define E2D_ENGINE_SCENE_OPTIMIZATION_H

#include "e2d/Engine/Common.h"

namespace e2d {
	namespace engine {
		class IOptimizableEntity {
		public:
			IOptimizableEntity() {};
			virtual ~IOptimizableEntity() {};
		
			void LoadDeferred(DeferredDataKind::Kind kind) {
				if (loadRequestsCounters.count(kind) == 0) {
					loadRequestsCounters[kind] = 0;
				}

				int& loadRequestsCounter = loadRequestsCounters[kind];
				if (loadRequestsCounter == 0) {
					LoadDeferredData(kind);
				}
				
				loadRequestsCounter++;
			};

			void UnloadDeferred(DeferredDataKind::Kind kind) {
				if (loadRequestsCounters.count(kind) == 0) {
					return;
				}
				
				int& loadRequestsCounter = loadRequestsCounters[kind];
				if (loadRequestsCounter == 1) {
					UnloadDeferredData(kind);
				}
				
				loadRequestsCounter--;
			};

			virtual Rect GetBoundingBox(DeferredDataKind::Kind kind) = 0;
			virtual void LoadDeferredData(DeferredDataKind::Kind kind) = 0;
			virtual void UnloadDeferredData(DeferredDataKind::Kind kind) = 0;
		
		private:
			typedef std::map<DeferredDataKind::Kind, int> LoadRequestsCounters;
			LoadRequestsCounters loadRequestsCounters;

			friend class Scene;
		};

		class FloatingDeferredDataWindow {
		public:
			FloatingDeferredDataWindow(const vec2& position, float windowWidth, float criticalDistanceToEdge):
				windowWidth(windowWidth),
				criticalDistanceToEdge(criticalDistanceToEdge),
				x1(position.x - windowWidth * 0.5f),
				x2(x1 + windowWidth) {
			};
		
			Rect GetRect() {
				return Rect(x1, 0.0f, windowWidth, 0.0f);
			};
		
			Rect UpdateRect(const vec2& position) {
				if (position.x + criticalDistanceToEdge > x2) {
					x2 = position.x + criticalDistanceToEdge;
					x1 = x2 - windowWidth;
				}

				if (position.x - criticalDistanceToEdge <= x1) {
					x1 = position.x - criticalDistanceToEdge;
					x2 = x1 + windowWidth;
				}

				return GetRect();
			};

		private:
			float x1;
			float x2;
			float windowWidth;
			float criticalDistanceToEdge;
		};

		// T should implement IOptimizableEntity interface
		template<class T, DeferredDataKind::Kind kind>
		class HorizontalBlockOptimizer {
		public:
			typedef std::vector<int> HorizontalBlocksIndices;
			typedef std::vector<T*> HorizontalBlock;

			struct BlocksRange {
				BlocksRange():
					firstBlock(0),
					lastBlock(0) {
				};

				BlocksRange(int firstBlock, int lastBlock):
					firstBlock(firstBlock),
					lastBlock(lastBlock) {
					CGL_CHECK(firstBlock <= lastBlock);
				};

				bool operator == (const BlocksRange& range) {
					return firstBlock == range.firstBlock && lastBlock == range.lastBlock;
				}

				void OverallRange(const BlocksRange& range) {
					firstBlock = std::min(firstBlock, range.firstBlock);
					lastBlock = std::max(lastBlock, range.lastBlock);
				}

				BlocksRange& Clamp(const BlocksRange& maxRange) {
					if (firstBlock < maxRange.firstBlock)
						firstBlock = maxRange.firstBlock;

					if (lastBlock < maxRange.firstBlock)
						lastBlock = maxRange.firstBlock;

					if (firstBlock > maxRange.lastBlock)
						firstBlock = maxRange.lastBlock;

					if (lastBlock > maxRange.lastBlock)
						lastBlock = maxRange.lastBlock;

					return *this;
				}

				int firstBlock;
				int lastBlock;
			};

			HorizontalBlockOptimizer(const vec2& position, float windowWidth, float criticalDistanceToEdge, float blockWidth):
				blockWidth(blockWidth),
				sceneBlocksRange(0, 0),
				deferredDataWindow(position, windowWidth, criticalDistanceToEdge) {
				oldDeferredDataWindowRect = deferredDataWindow.GetRect();
			};
			~HorizontalBlockOptimizer() {};

			void AddEntity(T* entity) {
				BlocksRange blocksIndecies = GetBlocks(entity);
				for (int i = blocksIndecies.firstBlock; i < blocksIndecies.lastBlock; ++i) {
					horizontalBlocks[i].push_back(entity);
				}

				sceneBlocksRange.OverallRange(blocksIndecies);
			};

			void EntitiesAdded() {
				for (int i = sceneBlocksRange.firstBlock; i < sceneBlocksRange.lastBlock; ++i) {
					horizontalBlocks[i];
				}
			};

			BlocksRange GetBlocks(const math::RectFloat& rect) const {
				return BlocksRange(
					std::floorf(rect.x / blockWidth),
					std::ceilf((rect.x + rect.width) / blockWidth)
				);
			};

			HorizontalBlock& GetBlock(int blockIndex) {
				CGL_CHECK(horizontalBlocks.count(blockIndex) == 1);
				return horizontalBlocks.at(blockIndex);
			};

			void Update(const vec2& position) {
				Rect newEntitesWindowRect = deferredDataWindow.UpdateRect(position);
				BlocksRange oldBlockRange = GetBlocks(oldDeferredDataWindowRect);
				BlocksRange newBlockRange = GetBlocks(newEntitesWindowRect);
				vec2 direction = newEntitesWindowRect.get_center() - oldDeferredDataWindowRect.get_center();
			
				oldDeferredDataWindowRect = newEntitesWindowRect;

				if (oldBlockRange == newBlockRange)
					return;

				CGL_CHECK(direction.x != 0.0f);

				/* Calculate blocks to load and unload */
				BlocksRange rangeToUnload;
				BlocksRange rangeToLoad;
				if (direction.x > 0.0f) {
					rangeToUnload.firstBlock = oldBlockRange.firstBlock;
					rangeToUnload.lastBlock = std::min(oldBlockRange.lastBlock, newBlockRange.firstBlock);
					rangeToLoad.firstBlock = std::max(oldBlockRange.lastBlock, newBlockRange.firstBlock);
					rangeToLoad.lastBlock = newBlockRange.lastBlock;
				} else {
					rangeToUnload.firstBlock = std::max(oldBlockRange.firstBlock, newBlockRange.lastBlock);
					rangeToUnload.lastBlock = oldBlockRange.lastBlock;
					rangeToLoad.firstBlock = newBlockRange.firstBlock;
					rangeToLoad.lastBlock = std::min(oldBlockRange.firstBlock, newBlockRange.lastBlock);
				}
			
				LoadDeferred(rangeToLoad.Clamp(sceneBlocksRange));
				UnloadDeferred(rangeToUnload.Clamp(sceneBlocksRange));
			};

		private:
			void LoadDeferred(const BlocksRange& range) {
				// Загружаем "отложенные" данные в сущности, попавшие в границы "окна"
				for (int blockIndex = range.firstBlock; blockIndex < range.lastBlock; ++blockIndex) {
					HorizontalBlock& block = GetBlock(blockIndex);
					for (HorizontalBlock::iterator blockIterator = block.begin(); blockIterator != block.end(); ++blockIterator) {
						(*blockIterator)->LoadDeferred(kind);
					}
				}
			};

			void UnloadDeferred(const BlocksRange& range) {
				// Выгружаем "отложенные" данные из сущностей, оказавшихся вне границ "окна"
				for (int blockIndex = range.firstBlock; blockIndex < range.lastBlock; ++blockIndex) {
					HorizontalBlock& block = GetBlock(blockIndex);
					for (HorizontalBlock::iterator blockIterator = block.begin(); blockIterator != block.end(); ++blockIterator) {
						(*blockIterator)->UnloadDeferred(kind);
					}
				}
			};

			BlocksRange GetBlocks(T* entity) const {
				return GetBlocks(entity->GetBoundingBox(kind));
			}

			typedef std::map<int, HorizontalBlock> HorizontalBlocks;
			HorizontalBlocks horizontalBlocks;
			BlocksRange sceneBlocksRange;
			float blockWidth;
			// "Loaded" entities window
			FloatingDeferredDataWindow deferredDataWindow;
			Rect oldDeferredDataWindowRect;
		};
	}
}

#endif