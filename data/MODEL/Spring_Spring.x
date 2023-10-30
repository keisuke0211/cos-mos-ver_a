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
 81;
 4.17713;2.77241;0.95548;,
 5.96036;1.37695;0.95548;,
 4.20808;1.37695;-3.38172;,
 2.94714;2.77241;-2.01397;,
 4.17713;0.07755;0.95548;,
 2.94714;0.07755;-2.01397;,
 -0.02230;1.37695;-5.17825;,
 -0.02230;2.77241;-3.24395;,
 -0.02230;0.07755;-3.24395;,
 -4.25269;1.37695;-3.38172;,
 -2.99175;2.77241;-2.01397;,
 -2.99175;0.07755;-2.01397;,
 -6.00497;1.37695;0.95548;,
 -4.22173;2.77241;0.95548;,
 -4.22173;0.07755;0.95548;,
 -4.25268;1.37695;5.29268;,
 -2.99175;2.77241;3.92493;,
 -2.99175;0.07755;3.92493;,
 -0.02230;1.37695;7.08921;,
 -0.02230;2.77241;5.15491;,
 -0.02230;0.07755;5.15491;,
 4.20808;1.37695;5.29268;,
 2.94714;2.77241;3.92493;,
 2.94714;0.07755;3.92493;,
 5.96036;1.37695;0.95548;,
 4.17713;2.77241;0.95548;,
 4.17713;0.07755;0.95548;,
 4.17713;5.53645;0.95548;,
 5.96036;4.16787;0.95548;,
 4.20808;4.16787;-3.38172;,
 2.94714;5.53645;-2.01397;,
 4.17713;2.77241;0.95548;,
 2.94714;2.77241;-2.01397;,
 -0.02230;4.16787;-5.17825;,
 -0.02230;5.53645;-3.24395;,
 -0.02230;2.77241;-3.24395;,
 -4.25269;4.16787;-3.38172;,
 -2.99175;5.53645;-2.01397;,
 -2.99175;2.77241;-2.01397;,
 -6.00497;4.16787;0.95548;,
 -4.22173;5.53645;0.95548;,
 -4.22173;2.77241;0.95548;,
 -4.25268;4.16787;5.29268;,
 -2.99175;5.53645;3.92493;,
 -2.99175;2.77241;3.92493;,
 -0.02230;4.16787;7.08921;,
 -0.02230;5.53645;5.15491;,
 -0.02230;2.77241;5.15491;,
 4.20808;4.16787;5.29268;,
 2.94714;5.53645;3.92493;,
 2.94714;2.77241;3.92493;,
 5.96036;4.16787;0.95548;,
 4.17713;5.53645;0.95548;,
 4.17713;2.77241;0.95548;,
 4.17713;8.20444;0.95548;,
 5.96036;6.90504;0.95548;,
 4.20808;6.90504;-3.38172;,
 2.94714;8.20444;-2.01397;,
 4.17713;5.53645;0.95548;,
 2.94714;5.53645;-2.01397;,
 -0.02230;6.90504;-5.17825;,
 -0.02230;8.20444;-3.24395;,
 -0.02230;5.53645;-3.24395;,
 -4.25269;6.90504;-3.38172;,
 -2.99175;8.20444;-2.01397;,
 -2.99175;5.53645;-2.01397;,
 -6.00497;6.90504;0.95548;,
 -4.22173;8.20444;0.95548;,
 -4.22173;5.53645;0.95548;,
 -4.25268;6.90504;5.29268;,
 -2.99175;8.20444;3.92493;,
 -2.99175;5.53645;3.92493;,
 -0.02230;6.90504;7.08921;,
 -0.02230;8.20444;5.15491;,
 -0.02230;5.53645;5.15491;,
 4.20808;6.90504;5.29268;,
 2.94714;8.20444;3.92493;,
 2.94714;5.53645;3.92493;,
 5.96036;6.90504;0.95548;,
 4.17713;8.20444;0.95548;,
 4.17713;5.53645;0.95548;;
 
 48;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;7,6,9,10;,
 4;6,8,11,9;,
 4;10,9,12,13;,
 4;9,11,14,12;,
 4;13,12,15,16;,
 4;12,14,17,15;,
 4;16,15,18,19;,
 4;15,17,20,18;,
 4;19,18,21,22;,
 4;18,20,23,21;,
 4;22,21,24,25;,
 4;21,23,26,24;,
 4;27,28,29,30;,
 4;28,31,32,29;,
 4;30,29,33,34;,
 4;29,32,35,33;,
 4;34,33,36,37;,
 4;33,35,38,36;,
 4;37,36,39,40;,
 4;36,38,41,39;,
 4;40,39,42,43;,
 4;39,41,44,42;,
 4;43,42,45,46;,
 4;42,44,47,45;,
 4;46,45,48,49;,
 4;45,47,50,48;,
 4;49,48,51,52;,
 4;48,50,53,51;,
 4;54,55,56,57;,
 4;55,58,59,56;,
 4;57,56,60,61;,
 4;56,59,62,60;,
 4;61,60,63,64;,
 4;60,62,65,63;,
 4;64,63,66,67;,
 4;63,65,68,66;,
 4;67,66,69,70;,
 4;66,68,71,69;,
 4;70,69,72,73;,
 4;69,71,74,72;,
 4;73,72,75,76;,
 4;72,74,77,75;,
 4;76,75,78,79;,
 4;75,77,80,78;;
 
 MeshMaterialList {
  10;
  48;
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1;;
  Material {
   0.800000;0.238400;0.360800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.414400;0.091200;0.216800;1.000000;;
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
   0.169600;0.677600;0.514400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.132000;0.452000;0.344800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.517600;0.602400;0.480000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.392000;0.429600;0.376800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Mushroom.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.586400;0.181600;0.100000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  48;
  0.613056;0.790039;-0.000000;,
  0.585674;-0.810546;-0.000000;,
  0.430117;0.798973;-0.420287;,
  0.410668;-0.818891;-0.400961;,
  0.000000;0.807747;-0.589529;,
  0.000000;-0.827078;-0.562087;,
  -0.430117;0.798974;-0.420286;,
  -0.410667;-0.818891;-0.400960;,
  -0.613056;0.790040;0.000001;,
  -0.585674;-0.810547;0.000001;,
  -0.430117;0.798973;0.420287;,
  -0.410668;-0.818891;0.400961;,
  0.000000;0.807747;0.589529;,
  0.000000;-0.827078;0.562087;,
  0.430117;0.798973;0.420287;,
  0.410668;-0.818891;0.400961;,
  0.605605;0.795765;-0.000000;,
  0.424821;0.804540;-0.415020;,
  0.000000;0.813156;-0.582045;,
  -0.424821;0.804541;-0.415020;,
  -0.605605;0.795766;0.000001;,
  -0.424821;0.804540;0.415020;,
  0.000000;0.813156;0.582046;,
  0.424821;0.804540;0.415020;,
  0.585675;0.810546;-0.000000;,
  0.410668;0.818891;-0.400961;,
  0.000000;0.827078;-0.562087;,
  -0.410668;0.818891;-0.400960;,
  -0.585674;0.810547;0.000000;,
  -0.410668;0.818891;0.400961;,
  0.000000;0.827078;0.562087;,
  0.410668;0.818891;0.400961;,
  0.613056;-0.790039;-0.000000;,
  0.430117;-0.798973;-0.420287;,
  0.000000;-0.807747;-0.589529;,
  -0.430117;-0.798974;-0.420286;,
  -0.613056;-0.790040;0.000001;,
  -0.430117;-0.798973;0.420287;,
  0.000000;-0.807747;0.589529;,
  0.430117;-0.798973;0.420287;,
  0.605608;-0.795763;-0.000000;,
  0.424823;-0.804538;-0.415022;,
  0.000000;-0.813154;-0.582048;,
  -0.424823;-0.804539;-0.415021;,
  -0.605607;-0.795764;0.000001;,
  -0.424823;-0.804538;0.415022;,
  0.000000;-0.813154;0.582048;,
  0.424823;-0.804538;0.415022;;
  48;
  4;0,0,2,2;,
  4;1,1,3,3;,
  4;2,2,4,4;,
  4;3,3,5,5;,
  4;4,4,6,6;,
  4;5,5,7,7;,
  4;6,6,8,8;,
  4;7,7,9,9;,
  4;8,8,10,10;,
  4;9,9,11,11;,
  4;10,10,12,12;,
  4;11,11,13,13;,
  4;12,12,14,14;,
  4;13,13,15,15;,
  4;14,14,0,0;,
  4;15,15,1,1;,
  4;16,16,17,17;,
  4;32,32,33,33;,
  4;17,17,18,18;,
  4;33,33,34,34;,
  4;18,18,19,19;,
  4;34,34,35,35;,
  4;19,19,20,20;,
  4;35,35,36,36;,
  4;20,20,21,21;,
  4;36,36,37,37;,
  4;21,21,22,22;,
  4;37,37,38,38;,
  4;22,22,23,23;,
  4;38,38,39,39;,
  4;23,23,16,16;,
  4;39,39,32,32;,
  4;24,24,25,25;,
  4;40,40,41,41;,
  4;25,25,26,26;,
  4;41,41,42,42;,
  4;26,26,27,27;,
  4;42,42,43,43;,
  4;27,27,28,28;,
  4;43,43,44,44;,
  4;28,28,29,29;,
  4;44,44,45,45;,
  4;29,29,30,30;,
  4;45,45,46,46;,
  4;30,30,31,31;,
  4;46,46,47,47;,
  4;31,31,24,24;,
  4;47,47,40,40;;
 }
 MeshTextureCoords {
  81;
  0.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.125000;0.375000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.500000;,
  0.250000;0.375000;,
  0.250000;0.625000;,
  0.375000;0.500000;,
  0.375000;0.375000;,
  0.375000;0.625000;,
  0.500000;0.500000;,
  0.500000;0.375000;,
  0.500000;0.625000;,
  0.625000;0.500000;,
  0.625000;0.375000;,
  0.625000;0.625000;,
  0.750000;0.500000;,
  0.750000;0.375000;,
  0.750000;0.625000;,
  0.875000;0.500000;,
  0.875000;0.375000;,
  0.875000;0.625000;,
  1.000000;0.500000;,
  1.000000;0.375000;,
  1.000000;0.625000;,
  0.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.125000;0.375000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.500000;,
  0.250000;0.375000;,
  0.250000;0.625000;,
  0.375000;0.500000;,
  0.375000;0.375000;,
  0.375000;0.625000;,
  0.500000;0.500000;,
  0.500000;0.375000;,
  0.500000;0.625000;,
  0.625000;0.500000;,
  0.625000;0.375000;,
  0.625000;0.625000;,
  0.750000;0.500000;,
  0.750000;0.375000;,
  0.750000;0.625000;,
  0.875000;0.500000;,
  0.875000;0.375000;,
  0.875000;0.625000;,
  1.000000;0.500000;,
  1.000000;0.375000;,
  1.000000;0.625000;,
  0.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.125000;0.375000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.500000;,
  0.250000;0.375000;,
  0.250000;0.625000;,
  0.375000;0.500000;,
  0.375000;0.375000;,
  0.375000;0.625000;,
  0.500000;0.500000;,
  0.500000;0.375000;,
  0.500000;0.625000;,
  0.625000;0.500000;,
  0.625000;0.375000;,
  0.625000;0.625000;,
  0.750000;0.500000;,
  0.750000;0.375000;,
  0.750000;0.625000;,
  0.875000;0.500000;,
  0.875000;0.375000;,
  0.875000;0.625000;,
  1.000000;0.500000;,
  1.000000;0.375000;,
  1.000000;0.625000;;
 }
}