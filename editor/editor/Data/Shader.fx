matrix gmp_world; 
matrix gmp_projection; 
matrix gmp_vp; 
matrix gmp_wvp;

struct VS_INPUT  { 
  float4 position: POSITION;
}; 

struct VS_OUTPUT  {
  float4 position: POSITION; 
  float4 diffuse: COLOR; 
};

VS_OUTPUT Main(VS_INPUT input) { 
  VS_OUTPUT output;
  output.position = mul(input.position, gmp_wvp); 
  
  return output; 
}