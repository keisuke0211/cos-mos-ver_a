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
 40;
 -7.50000;-10.00000;-2.50000;,
 -7.50000;0.00000;0.00000;,
 -5.73223;-10.00000;-1.76777;,
 -5.00000;-10.00000;0.00000;,
 -5.73223;-10.00000;1.76777;,
 -7.50000;-10.00000;2.50000;,
 -9.26777;-10.00000;1.76777;,
 -10.00000;-10.00000;0.00000;,
 -9.26777;-10.00000;-1.76777;,
 -7.50000;-10.00000;0.00000;,
 -2.50000;-10.00000;-2.50000;,
 -2.50000;0.00000;0.00000;,
 -0.73223;-10.00000;-1.76777;,
 0.00000;-10.00000;-0.00000;,
 -0.73223;-10.00000;1.76777;,
 -2.50000;-10.00000;2.50000;,
 -4.26777;-10.00000;1.76777;,
 -5.00000;-10.00000;0.00000;,
 -4.26777;-10.00000;-1.76777;,
 -2.50000;-10.00000;0.00000;,
 2.50000;-10.00000;-2.50000;,
 2.50000;0.00000;0.00000;,
 4.26777;-10.00000;-1.76777;,
 5.00000;-10.00000;-0.00000;,
 4.26777;-10.00000;1.76777;,
 2.50000;-10.00000;2.50000;,
 0.73223;-10.00000;1.76777;,
 0.00000;-10.00000;-0.00000;,
 0.73223;-10.00000;-1.76777;,
 2.50000;-10.00000;-0.00000;,
 7.50000;-10.00000;-2.50000;,
 7.50000;0.00000;0.00000;,
 9.26777;-10.00000;-1.76777;,
 10.00000;-10.00000;-0.00000;,
 9.26777;-10.00000;1.76777;,
 7.50000;-10.00000;2.50000;,
 5.73223;-10.00000;1.76777;,
 5.00000;-10.00000;-0.00000;,
 5.73223;-10.00000;-1.76777;,
 7.50000;-10.00000;-0.00000;;
 
 64;
 3;0,1,2;,
 3;2,1,3;,
 3;3,1,4;,
 3;4,1,5;,
 3;5,1,6;,
 3;6,1,7;,
 3;7,1,8;,
 3;8,1,0;,
 3;9,0,2;,
 3;9,2,3;,
 3;9,3,4;,
 3;9,4,5;,
 3;9,5,6;,
 3;9,6,7;,
 3;9,7,8;,
 3;9,8,0;,
 3;10,11,12;,
 3;12,11,13;,
 3;13,11,14;,
 3;14,11,15;,
 3;15,11,16;,
 3;16,11,17;,
 3;17,11,18;,
 3;18,11,10;,
 3;19,10,12;,
 3;19,12,13;,
 3;19,13,14;,
 3;19,14,15;,
 3;19,15,16;,
 3;19,16,17;,
 3;19,17,18;,
 3;19,18,10;,
 3;20,21,22;,
 3;22,21,23;,
 3;23,21,24;,
 3;24,21,25;,
 3;25,21,26;,
 3;26,21,27;,
 3;27,21,28;,
 3;28,21,20;,
 3;29,20,22;,
 3;29,22,23;,
 3;29,23,24;,
 3;29,24,25;,
 3;29,25,26;,
 3;29,26,27;,
 3;29,27,28;,
 3;29,28,20;,
 3;30,31,32;,
 3;32,31,33;,
 3;33,31,34;,
 3;34,31,35;,
 3;35,31,36;,
 3;36,31,37;,
 3;37,31,38;,
 3;38,31,30;,
 3;39,30,32;,
 3;39,32,33;,
 3;39,33,34;,
 3;39,34,35;,
 3;39,35,36;,
 3;39,36,37;,
 3;39,37,38;,
 3;39,38,30;;
 
 MeshMaterialList {
  1;
  64;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  }
 }
}
