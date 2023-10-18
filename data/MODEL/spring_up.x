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
 54;
 -16.00000;8.00000;8.00000;,
 -16.00000;4.80000;8.00000;,
 16.00000;4.80000;8.00000;,
 16.00000;8.00000;8.00000;,
 -16.00000;8.00000;-8.00000;,
 -16.00000;4.80000;-8.00000;,
 -16.00000;4.80000;8.00000;,
 -16.00000;8.00000;8.00000;,
 16.00000;8.00000;-8.00000;,
 16.00000;4.80000;-8.00000;,
 -16.00000;4.80000;-8.00000;,
 -16.00000;8.00000;-8.00000;,
 16.00000;8.00000;8.00000;,
 16.00000;4.80000;8.00000;,
 16.00000;4.80000;-8.00000;,
 16.00000;8.00000;-8.00000;,
 -16.00000;8.00000;8.00000;,
 16.00000;8.00000;8.00000;,
 -16.00000;4.80000;8.00000;,
 16.00000;4.80000;8.00000;,
 0.00000;4.80000;0.00000;,
 -2.82843;4.80000;2.82843;,
 0.00000;4.80000;4.00000;,
 0.00000;4.80000;0.00000;,
 -4.00000;4.80000;0.00000;,
 0.00000;4.80000;0.00000;,
 -2.82843;4.80000;-2.82843;,
 0.00000;4.80000;0.00000;,
 0.00000;4.80000;-4.00000;,
 0.00000;4.80000;0.00000;,
 2.82843;4.80000;-2.82843;,
 0.00000;4.80000;0.00000;,
 4.00000;4.80000;0.00000;,
 0.00000;4.80000;0.00000;,
 2.82843;4.80000;2.82843;,
 0.00000;4.80000;0.00000;,
 0.00000;4.80000;4.00000;,
 0.00000;-3.20000;0.00000;,
 0.00000;-3.20000;4.00000;,
 -2.82843;-3.20000;2.82843;,
 0.00000;-3.20000;0.00000;,
 -4.00000;-3.20000;0.00000;,
 0.00000;-3.20000;0.00000;,
 -2.82843;-3.20000;-2.82843;,
 0.00000;-3.20000;0.00000;,
 0.00000;-3.20000;-4.00000;,
 0.00000;-3.20000;0.00000;,
 2.82843;-3.20000;-2.82843;,
 0.00000;-3.20000;0.00000;,
 4.00000;-3.20000;0.00000;,
 0.00000;-3.20000;0.00000;,
 2.82843;-3.20000;2.82843;,
 0.00000;-3.20000;0.00000;,
 0.00000;-3.20000;4.00000;;
 
 44;
 3;0,1,2;,
 3;0,2,3;,
 3;4,5,6;,
 3;4,6,7;,
 3;8,9,10;,
 3;8,10,11;,
 3;12,13,14;,
 3;12,14,15;,
 3;4,16,17;,
 3;4,17,15;,
 3;18,5,14;,
 3;18,14,19;,
 3;20,21,22;,
 3;23,24,21;,
 3;25,26,24;,
 3;27,28,26;,
 3;29,30,28;,
 3;31,32,30;,
 3;33,34,32;,
 3;35,36,34;,
 3;37,38,39;,
 3;40,39,41;,
 3;42,41,43;,
 3;44,43,45;,
 3;46,45,47;,
 3;48,47,49;,
 3;50,49,51;,
 3;52,51,53;,
 3;21,39,38;,
 3;21,38,22;,
 3;24,41,39;,
 3;24,39,21;,
 3;26,43,41;,
 3;26,41,24;,
 3;28,45,43;,
 3;28,43,26;,
 3;30,47,45;,
 3;30,45,28;,
 3;32,49,47;,
 3;32,47,30;,
 3;34,51,49;,
 3;34,49,32;,
 3;36,53,51;,
 3;36,51,34;;
 
 MeshMaterialList {
  5;
  44;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\IMG_5307.PNG";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\IMG_5308.PNG";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\IMG_5310.PNG";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\IMG_5311.PNG";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\IMG_5312.PNG";
   }
  }
 }
 MeshNormals {
  22;
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.603748;0.000000;0.797176;,
  -0.797176;0.000000;0.603748;,
  -0.136773;0.000000;0.990602;,
  0.136773;0.000000;0.990602;,
  -0.990602;0.000000;0.136773;,
  -0.990602;0.000000;-0.136773;,
  -0.797176;0.000000;-0.603748;,
  -0.603748;0.000000;-0.797176;,
  -0.136773;0.000000;-0.990602;,
  0.136773;0.000000;-0.990602;,
  0.603748;0.000000;-0.797176;,
  0.797176;0.000000;-0.603748;,
  0.990602;0.000000;-0.136773;,
  0.990602;0.000000;0.136773;,
  0.797176;0.000000;0.603748;,
  0.603748;0.000000;0.797176;;
  44;
  3;0,0,0;,
  3;0,0,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;2,2,2;,
  3;2,2,2;,
  3;5,5,5;,
  3;5,5,5;,
  3;3,3,3;,
  3;3,3,3;,
  3;4,4,4;,
  3;4,4,4;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;6,7,8;,
  3;6,8,9;,
  3;10,11,7;,
  3;10,7,6;,
  3;12,13,11;,
  3;12,11,10;,
  3;14,15,13;,
  3;14,13,12;,
  3;16,17,15;,
  3;16,15,14;,
  3;18,19,17;,
  3;18,17,16;,
  3;20,21,19;,
  3;20,19,18;,
  3;9,8,21;,
  3;9,21,20;;
 }
 MeshTextureCoords {
  54;
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;;
 }
}
