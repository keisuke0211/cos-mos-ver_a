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
 17;
 -15.92712;-0.96289;9.46400;,
 -24.00000;23.99906;0.20944;,
 -24.00000;-4.18223;-0.03650;,
 3.70666;-14.48671;5.80612;,
 -8.47705;-23.99906;-0.20944;,
 6.23149;-23.99906;-0.20944;,
 16.45105;-23.99906;-0.20944;,
 24.00000;-23.99906;-0.20944;,
 24.00000;1.35719;0.01184;,
 12.73448;-7.43831;2.56080;,
 -24.00000;-23.99906;-0.20944;,
 24.00000;14.95946;0.13055;,
 24.00000;23.99906;0.20944;,
 5.67930;23.99906;0.20944;,
 9.04626;8.99613;7.64837;,
 -6.50849;23.99906;0.20944;,
 -1.41862;4.82289;0.04209;;
 
 20;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;6,8,9;,
 3;2,10,4;,
 3;2,4,0;,
 3;11,12,13;,
 3;11,13,14;,
 3;14,9,8;,
 3;14,8,11;,
 3;5,6,9;,
 3;5,9,3;,
 3;15,1,0;,
 3;15,0,16;,
 3;16,14,13;,
 3;16,13,15;,
 3;0,4,3;,
 3;0,3,16;,
 3;16,3,9;,
 3;16,9,14;;
 
 MeshMaterialList {
  2;
  20;
  1,
  1,
  0,
  1,
  0,
  1,
  0,
  0,
  1,
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
  1;;
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
   0.489412;0.489412;0.489412;1.000000;;
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
  -0.424633;0.190794;0.885034;,
  -0.000000;-0.008727;0.999962;,
  0.000000;-0.008727;0.999962;,
  -0.106846;0.185824;0.976756;,
  0.097551;-0.090430;0.991114;,
  0.281028;-0.079310;0.956417;,
  -0.188469;-0.379683;0.905715;,
  0.152466;-0.153762;0.976274;,
  0.240736;0.159754;0.957353;,
  -0.257964;-0.044506;0.965129;,
  0.170001;-0.025362;0.985118;,
  -0.497040;-0.177313;0.849418;,
  0.175423;0.161851;0.971098;,
  0.190224;-0.364993;0.911370;,
  0.208336;-0.140800;0.967870;,
  0.122743;0.095234;0.987859;,
  0.504323;0.126406;0.854213;,
  -0.630181;0.226776;0.742593;;
  20;
  3;10,1,12;,
  3;15,7,14;,
  3;5,2,6;,
  3;5,6,8;,
  3;12,3,7;,
  3;12,7,10;,
  3;9,0,4;,
  3;9,4,11;,
  3;11,8,6;,
  3;11,6,9;,
  3;14,5,8;,
  3;14,8,15;,
  3;13,1,10;,
  3;13,17,16;,
  3;18,18,4;,
  3;16,4,13;,
  3;10,7,15;,
  3;10,15,16;,
  3;16,15,8;,
  3;16,8,11;;
 }
 MeshTextureCoords {
  17;
  0.831815;0.520061;,
  1.000000;0.000000;,
  1.000000;0.587133;,
  0.422778;0.801818;,
  0.676605;1.000000;,
  0.370177;1.000000;,
  0.157270;1.000000;,
  0.000000;1.000000;,
  0.000000;0.471724;,
  0.234698;0.654971;,
  1.000000;1.000000;,
  0.000000;0.188332;,
  0.000000;0.000000;,
  0.381681;0.000000;,
  0.311536;0.312573;,
  0.635594;0.000000;,
  0.529555;0.399519;;
 }
}
