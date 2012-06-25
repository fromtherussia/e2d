#ifndef R2D_D3D_GEOMETRY_DEFINITIONS_H
#define R2D_D3D_GEOMETRY_DEFINITIONS_H

namespace r2d {
	struct WireGeometryVertex {
		FLOAT x, y, z;
		DWORD color;
	};

	struct WireGeometryPoint {
		FLOAT x, y, z;
		FLOAT size;
		DWORD color;
	};

	struct StaticGeometryVertex {
		FLOAT x, y, z;
		DWORD color;
		FLOAT u, v;
	};

	#define AXIS_LENGTH 20.0f
	#define MAX_ZCHOOORD 0.5f
	#define D3DFVF_WIRE_GEOMETRY_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)
	#define D3DFVF_WIRE_GEOMETRY_POINT (D3DFVF_PSIZE | D3DFVF_XYZ | D3DFVF_DIFFUSE)
	#define D3DFVF_STATIC_GEOMETRY_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
}

#endif
