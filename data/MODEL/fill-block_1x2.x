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
 16;
 -8.00000;-7.17611;0.00000;,
 -8.00000;-15.99999;0.00001;,
 -2.47050;-15.99999;0.00001;,
 8.00000;3.07487;-0.00000;,
 8.00000;15.99999;-0.00001;,
 3.76980;9.87252;-0.00000;,
 -0.04331;15.99999;-0.00001;,
 -8.00000;8.91442;-0.00000;,
 -0.87310;3.14725;3.69633;,
 1.29335;-11.69817;3.09957;,
 4.30309;-15.99999;0.00001;,
 -8.00000;1.58478;-0.00000;,
 -4.95570;-2.76643;0.00000;,
 8.00000;-4.03295;0.00000;,
 -8.00000;15.99999;-0.00001;,
 8.00000;-15.99999;0.00001;;
 
 18;
 3;0,1,2;,
 3;3,4,5;,
 3;5,4,6;,
 3;5,7,8;,
 3;9,2,10;,
 3;11,0,12;,
 3;3,5,8;,
 3;3,8,13;,
 3;6,14,7;,
 3;6,7,5;,
 3;0,2,9;,
 3;0,9,12;,
 3;12,9,13;,
 3;12,13,8;,
 3;10,15,13;,
 3;10,13,9;,
 3;11,12,8;,
 3;11,8,7;;
 
 MeshMaterialList {
  2;
  18;
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  1,
  0,
  1,
  1,
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
   0.461176;0.461176;0.461176;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTUTE\\rock.jpg";
   }
  }
 }
 MeshNormals {
  15;
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.169005;-0.024901;0.985301;,
  -0.146882;-0.297689;0.943296;,
  0.203281;-0.071804;0.976484;,
  -0.131317;0.131704;0.982553;,
  -0.034785;-0.008277;0.999361;,
  0.259413;0.079759;0.962467;,
  0.069294;0.152531;0.985866;,
  -0.000000;0.000000;1.000000;,
  0.205780;-0.273822;0.939508;,
  -0.138393;-0.056923;0.988740;,
  -0.011393;-0.115575;0.993233;,
  -0.294028;-0.094890;0.951075;;
  18;
  3;3,2,4;,
  3;8,0,9;,
  3;9,0,10;,
  3;9,6,7;,
  3;13,4,11;,
  3;14,3,12;,
  3;8,9,7;,
  3;8,7,5;,
  3;10,1,6;,
  3;10,6,9;,
  3;3,4,13;,
  3;3,13,12;,
  3;12,13,5;,
  3;12,5,7;,
  3;11,1,5;,
  3;11,5,13;,
  3;14,12,7;,
  3;14,7,6;;
 }
 MeshTextureCoords {
  16;
  1.000000;0.724254;,
  1.000000;1.000000;,
  0.654406;1.000000;,
  0.000000;0.403910;,
  0.000000;0.000000;,
  0.264387;0.191483;,
  0.502707;0.000000;,
  1.000000;0.221424;,
  0.554569;0.401648;,
  0.419166;0.865568;,
  0.231057;1.000000;,
  1.000000;0.450476;,
  0.809731;0.586451;,
  0.000000;0.626030;,
  1.000000;0.000000;,
  0.000000;1.000000;;
 }
}
