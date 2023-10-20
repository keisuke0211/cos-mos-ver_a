xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 21;
 3.12475;7.99969;0.06981;,
 -4.45273;7.99969;0.06981;,
 -0.67578;6.59482;0.05755;,
 -0.01184;-2.08717;0.84519;,
 -21.24096;-7.99969;-0.06981;,
 5.06396;-7.99969;-0.06981;,
 24.00000;0.08934;0.00078;,
 24.00000;7.99969;0.06981;,
 15.88635;7.99969;0.06981;,
 12.95578;1.52444;4.29489;,
 24.00000;-2.58356;-0.02255;,
 19.68979;-7.99969;-0.06981;,
 24.00000;-7.99969;-0.06981;,
 -24.00000;-2.02701;-0.01769;,
 -24.00000;-7.99969;-0.06981;,
 -16.14626;0.87613;3.98117;,
 -12.05735;7.99969;0.06981;,
 -24.00000;7.99969;0.06981;,
 8.37746;7.99969;0.06981;,
 -8.67125;7.99969;0.06981;,
 -5.82966;4.68968;0.70857;;
 
 24;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;6,9,10;,
 3;11,12,10;,
 3;11,10,9;,
 3;13,14,4;,
 3;13,4,15;,
 3;15,16,17;,
 3;15,17,13;,
 3;0,2,9;,
 3;0,9,18;,
 3;5,11,9;,
 3;5,9,3;,
 3;19,16,15;,
 3;19,15,20;,
 3;20,2,1;,
 3;20,1,19;,
 3;15,4,3;,
 3;15,3,20;,
 3;3,9,2;,
 3;3,2,20;,
 3;8,18,9;,
 3;8,9,6;;
 
 MeshMaterialList {
  2;
  24;
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTUTE\\rock.jpg";
   }
  }
  Material {
   0.495686;0.495686;0.495686;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTUTE\\rock.jpg";
   }
  }
 }
 MeshNormals {
  19;
  0.000000;-0.008727;0.999962;,
  -0.239369;0.251073;0.937904;,
  0.000000;0.546457;0.837487;,
  0.095208;-0.223746;0.969986;,
  0.000000;0.481295;0.876559;,
  -0.077740;-0.207818;0.975073;,
  0.217381;-0.083832;0.972480;,
  0.052804;0.118891;0.991502;,
  0.021415;0.115213;0.993110;,
  -0.287558;-0.069873;0.955211;,
  -0.049286;0.315758;0.947559;,
  -0.055705;0.133384;0.989498;,
  -0.053684;0.142010;0.988408;,
  -0.057010;-0.289665;0.955429;,
  0.058445;0.336778;0.939768;,
  -0.007192;-0.091451;0.995784;,
  0.110795;0.199036;0.973709;,
  0.255204;0.125388;0.958723;,
  0.132076;0.320941;0.937845;;
  24;
  3;10,8,12;,
  3;15,5,13;,
  3;17,0,18;,
  3;17,7,6;,
  3;3,0,6;,
  3;3,6,7;,
  3;9,0,5;,
  3;9,5,11;,
  3;11,4,1;,
  3;11,1,9;,
  3;10,12,7;,
  3;10,7,2;,
  3;13,3,7;,
  3;13,7,15;,
  3;14,4,11;,
  3;14,11,16;,
  3;16,12,8;,
  3;16,8,14;,
  3;11,5,15;,
  3;11,15,16;,
  3;15,7,12;,
  3;15,12,16;,
  3;18,2,7;,
  3;18,7,17;;
 }
 MeshTextureCoords {
  21;
  0.434901;0.000000;,
  0.592765;0.000000;,
  0.514079;0.087808;,
  0.500247;0.630453;,
  0.942520;1.000000;,
  0.394501;1.000000;,
  0.000000;0.494416;,
  0.000000;0.000000;,
  0.169034;0.000000;,
  0.230088;0.404719;,
  0.000000;0.661479;,
  0.089796;1.000000;,
  0.000000;1.000000;,
  1.000000;0.626693;,
  1.000000;1.000000;,
  0.836380;0.445240;,
  0.751195;0.000000;,
  1.000000;0.000000;,
  0.325470;0.000000;,
  0.680651;0.000000;,
  0.621451;0.206884;;
 }
}
