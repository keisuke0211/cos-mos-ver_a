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
 59;
 0.00000;-8.00000;-0.00000;,
 -2.16479;-7.39104;-2.16478;,
 0.00000;-7.39104;-3.06147;,
 -3.06147;-7.39104;0.00000;,
 2.16479;-7.39104;-2.16478;,
 3.06147;-7.39104;-0.00000;,
 -4.00000;-5.65686;-4.00000;,
 0.00000;-5.65686;-5.65685;,
 -5.65686;-5.65686;0.00000;,
 4.00000;-5.65686;-4.00000;,
 5.65686;-5.65686;-0.00000;,
 -5.22625;-3.06147;-5.22625;,
 0.00000;-3.06147;-7.39104;,
 -7.39104;-3.06147;0.00000;,
 5.22625;-3.06147;-5.22625;,
 7.39104;-3.06147;-0.00000;,
 -5.65686;0.00000;-5.65685;,
 0.00000;0.00000;-8.00000;,
 -8.00000;0.00000;0.00000;,
 5.65686;0.00000;-5.65685;,
 8.00000;0.00000;0.00000;,
 0.00000;-7.39104;3.06147;,
 -2.16479;-7.39104;2.16478;,
 2.16479;-7.39104;2.16478;,
 0.00000;-5.65686;5.65685;,
 -4.00000;-5.65686;4.00000;,
 4.00000;-5.65686;4.00000;,
 0.00000;-3.06147;7.39104;,
 -5.22625;-3.06147;5.22625;,
 5.22625;-3.06147;5.22625;,
 0.00000;0.00000;8.00000;,
 -5.65686;0.00000;5.65685;,
 8.00000;0.00000;0.00000;,
 5.65686;0.00000;5.65685;,
 -0.52276;-8.90752;-1.42466;,
 -1.52866;-8.81878;-1.01758;,
 -1.55386;-6.80682;-1.13379;,
 -0.28223;-6.91900;-1.64840;,
 -1.96000;-8.84475;0.00000;,
 -2.09900;-6.83875;0.00000;,
 0.86500;-9.18375;-0.00000;,
 0.52276;-8.90752;-1.42466;,
 0.97118;-7.10987;-1.11267;,
 1.47200;-7.26775;-0.00000;,
 -0.91553;-10.03712;-1.22463;,
 -1.51600;-10.72075;0.00000;,
 -1.72956;-9.92686;-0.90539;,
 -2.07700;-9.95875;0.00000;,
 0.14300;-10.36175;-0.00000;,
 -0.14374;-10.21821;-0.87169;,
 -0.52276;-8.90752;1.42466;,
 -0.28223;-6.91900;1.64840;,
 -1.55386;-6.80682;1.13379;,
 -1.52866;-8.81878;1.01758;,
 0.97118;-7.10987;1.11267;,
 0.52276;-8.90752;1.42466;,
 -0.91553;-10.03712;1.22463;,
 -1.72956;-9.92686;0.90539;,
 -0.14374;-10.21821;0.87169;;
 
 56;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,5;,
 3;0,2,4;,
 4;2,1,6,7;,
 4;1,3,8,6;,
 4;5,4,9,10;,
 4;4,2,7,9;,
 4;7,6,11,12;,
 4;6,8,13,11;,
 4;10,9,14,15;,
 4;9,7,12,14;,
 4;12,11,16,17;,
 4;11,13,18,16;,
 4;15,14,19,20;,
 4;14,12,17,19;,
 3;0,21,22;,
 3;0,22,3;,
 3;0,5,23;,
 3;0,23,21;,
 4;21,24,25,22;,
 4;22,25,8,3;,
 4;5,10,26,23;,
 4;23,26,24,21;,
 4;24,27,28,25;,
 4;25,28,13,8;,
 4;10,15,29,26;,
 4;26,29,27,24;,
 4;27,30,31,28;,
 4;28,31,18,13;,
 4;15,32,33,29;,
 4;29,33,30,27;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;40,41,42,43;,
 4;41,34,37,42;,
 3;44,45,46;,
 4;44,46,35,34;,
 3;46,45,47;,
 4;46,47,38,35;,
 3;48,45,49;,
 4;48,49,41,40;,
 3;49,45,44;,
 4;49,44,34,41;,
 4;50,51,52,53;,
 4;53,52,39,38;,
 4;40,43,54,55;,
 4;55,54,51,50;,
 3;56,57,45;,
 4;56,50,53,57;,
 3;57,47,45;,
 4;57,53,38,47;,
 3;48,58,45;,
 4;48,40,55,58;,
 3;58,56,45;,
 4;58,55,50,56;;
 
 MeshMaterialList {
  6;
  56;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.561600;0.800000;0.254400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.737600;0.712000;0.153600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.119200;0.150400;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.668000;0.332800;0.712000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  60;
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.924736;-0.380610;,
  -0.269132;-0.924736;-0.269132;,
  0.269132;-0.924736;-0.269132;,
  0.000000;-0.709231;-0.704976;,
  -0.498494;-0.709230;-0.498494;,
  0.498494;-0.709230;-0.498494;,
  0.000000;-0.384551;-0.923104;,
  -0.652733;-0.384551;-0.652733;,
  -0.923104;-0.384551;-0.000000;,
  0.652733;-0.384551;-0.652733;,
  0.000000;-0.195090;-0.980785;,
  -0.693520;-0.195090;-0.693520;,
  -0.980785;-0.195091;0.000000;,
  0.908663;-0.180745;-0.376381;,
  0.693520;-0.195090;-0.693520;,
  0.000000;-0.924736;0.380610;,
  -0.269132;-0.924736;0.269132;,
  -0.380610;-0.924736;0.000000;,
  0.380610;-0.924736;-0.000000;,
  0.269132;-0.924736;0.269132;,
  0.000000;-0.709231;0.704976;,
  -0.498494;-0.709230;0.498494;,
  -0.704977;-0.709230;-0.000000;,
  0.704977;-0.709230;-0.000000;,
  0.498494;-0.709230;0.498494;,
  0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  0.923104;-0.384551;-0.000000;,
  0.652733;-0.384551;0.652733;,
  0.000000;-0.195090;0.980785;,
  -0.693520;-0.195090;0.693520;,
  0.908663;-0.180745;0.376381;,
  0.693520;-0.195090;0.693520;,
  -0.246716;-0.963839;-0.100723;,
  -0.097773;-0.119612;-0.987995;,
  -0.700452;-0.006987;-0.713666;,
  -0.999422;0.033993;0.000000;,
  0.916973;-0.398950;-0.000000;,
  0.597961;-0.317710;-0.735869;,
  -0.090945;-0.044552;-0.994859;,
  -0.692981;-0.058135;-0.718608;,
  -0.998493;-0.054888;0.000000;,
  0.968707;-0.248207;-0.000000;,
  0.636077;-0.148440;-0.757213;,
  -0.689452;-0.354546;-0.631627;,
  -0.143259;-0.558987;-0.816707;,
  -0.966128;-0.258063;0.000000;,
  0.566327;-0.824181;-0.000000;,
  0.339313;-0.760440;-0.553712;,
  -0.097773;-0.119612;0.987995;,
  -0.700452;-0.006987;0.713666;,
  0.597961;-0.317710;0.735869;,
  -0.090945;-0.044552;0.994859;,
  -0.692981;-0.058135;0.718608;,
  0.636077;-0.148440;0.757213;,
  -0.689452;-0.354546;0.631627;,
  -0.143259;-0.558987;0.816707;,
  0.339313;-0.760440;0.553712;,
  -0.327877;-0.747314;0.577943;;
  56;
  3;0,2,1;,
  3;0,18,2;,
  3;0,3,19;,
  3;0,1,3;,
  4;1,2,5,4;,
  4;2,18,23,5;,
  4;19,3,6,24;,
  4;3,1,4,6;,
  4;4,5,8,7;,
  4;5,23,9,8;,
  4;24,6,10,28;,
  4;6,4,7,10;,
  4;7,8,12,11;,
  4;8,9,13,12;,
  4;28,10,15,14;,
  4;10,7,11,15;,
  3;0,16,17;,
  3;0,17,18;,
  3;0,19,20;,
  3;0,20,16;,
  4;16,21,22,17;,
  4;17,22,23,18;,
  4;19,24,25,20;,
  4;20,25,21,16;,
  4;21,26,27,22;,
  4;22,27,9,23;,
  4;24,28,29,25;,
  4;25,29,26,21;,
  4;26,30,31,27;,
  4;27,31,13,9;,
  4;28,32,33,29;,
  4;29,33,30,26;,
  4;35,36,41,40;,
  4;36,37,42,41;,
  4;38,39,44,43;,
  4;39,35,40,44;,
  3;46,34,45;,
  4;46,45,36,35;,
  3;45,34,47;,
  4;45,47,37,36;,
  3;48,34,49;,
  4;48,49,39,38;,
  3;49,34,46;,
  4;49,46,35,39;,
  4;50,53,54,51;,
  4;51,54,42,37;,
  4;38,43,55,52;,
  4;52,55,53,50;,
  3;57,56,59;,
  4;57,50,51,56;,
  3;56,47,34;,
  4;56,51,37,47;,
  3;48,58,34;,
  4;48,38,52,58;,
  3;58,57,34;,
  4;58,52,50,57;;
 }
 MeshTextureCoords {
  59;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
