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
 58;
 0.07880;0.00312;4.01484;,
 0.90683;0.83115;3.78191;,
 0.07880;1.17413;3.78191;,
 1.24982;0.00312;3.78191;,
 0.90683;-0.82491;3.78191;,
 0.07880;-1.16789;3.78191;,
 -0.74922;-0.82491;3.78191;,
 -1.09221;0.00312;3.78191;,
 -0.74922;0.83115;3.78191;,
 1.60880;1.53312;3.11858;,
 0.07880;2.16686;3.11858;,
 2.24255;0.00312;3.11858;,
 1.60880;-1.52688;3.11858;,
 0.07880;-2.16063;3.11858;,
 -1.45119;-1.52688;3.11858;,
 -2.08494;0.00312;3.11858;,
 -1.45119;1.53312;3.11858;,
 2.07785;2.00216;2.12585;,
 0.07880;2.83019;2.12585;,
 2.90588;0.00312;2.12585;,
 2.07785;-1.99592;2.12585;,
 0.07880;-2.82395;2.12585;,
 -1.92024;-1.99592;2.12585;,
 -2.74827;0.00312;2.12585;,
 -1.92024;2.00216;2.12585;,
 2.24255;2.16686;0.95484;,
 0.07880;3.06312;0.95484;,
 3.13881;0.00312;0.95484;,
 2.24255;-2.16063;0.95484;,
 0.07880;-3.05688;0.95484;,
 -2.08494;-2.16063;0.95484;,
 -2.98120;0.00312;0.95484;,
 -2.08494;2.16686;0.95484;,
 2.07785;2.00216;-0.21617;,
 0.07880;2.83019;-0.21617;,
 2.90588;0.00312;-0.21617;,
 2.07785;-1.99592;-0.21617;,
 0.07880;-2.82395;-0.21617;,
 -1.92024;-1.99592;-0.21617;,
 -2.74827;0.00312;-0.21617;,
 -1.92024;2.00216;-0.21617;,
 1.60880;1.53312;-1.20891;,
 0.07880;2.16686;-1.20891;,
 2.24255;0.00312;-1.20891;,
 1.60880;-1.52688;-1.20891;,
 0.07880;-2.16063;-1.20891;,
 -1.45119;-1.52688;-1.20891;,
 -2.08494;0.00312;-1.20891;,
 -1.45119;1.53312;-1.20891;,
 0.69983;0.62414;-1.90135;,
 0.07880;0.88138;-1.90135;,
 0.95706;0.00312;-1.90135;,
 0.69983;-0.61791;-1.90135;,
 0.07880;-0.87514;-1.90135;,
 -0.54222;-0.61790;-1.90135;,
 -0.79945;0.00312;-1.90135;,
 -0.54222;0.62414;-1.90135;,
 0.07880;0.00312;-2.07605;;
 
 64;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 3;50,49,57;,
 3;49,51,57;,
 3;51,52,57;,
 3;52,53,57;,
 3;53,54,57;,
 3;54,55,57;,
 3;55,56,57;,
 3;56,50,57;;
 
 MeshMaterialList {
  10;
  64;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8;;
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
  58;
  -0.000001;0.000000;1.000000;,
  -0.000001;0.380614;0.924734;,
  0.269134;0.269136;0.924734;,
  0.380613;0.000000;0.924735;,
  0.269133;-0.269135;0.924734;,
  -0.000001;-0.380612;0.924735;,
  -0.269135;-0.269135;0.924734;,
  -0.380613;0.000000;0.924734;,
  -0.269135;0.269136;0.924734;,
  -0.000001;0.704977;0.709230;,
  0.498492;0.498495;0.709231;,
  0.704976;0.000000;0.709231;,
  0.498493;-0.498495;0.709230;,
  -0.000001;-0.704977;0.709230;,
  -0.498494;-0.498494;0.709230;,
  -0.704976;0.000000;0.709231;,
  -0.498493;0.498495;0.709231;,
  -0.000001;0.923103;0.384552;,
  0.652732;0.652733;0.384553;,
  0.923103;0.000000;0.384554;,
  0.652732;-0.652733;0.384553;,
  -0.000001;-0.923103;0.384552;,
  -0.652732;-0.652733;0.384553;,
  -0.923103;0.000000;0.384554;,
  -0.652732;0.652733;0.384553;,
  -0.000001;1.000000;-0.000000;,
  0.707106;0.707107;-0.000000;,
  1.000000;0.000000;-0.000000;,
  0.707106;-0.707108;-0.000000;,
  -0.000001;-1.000000;-0.000000;,
  -0.707106;-0.707107;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.707107;0.000000;,
  -0.000001;0.923104;-0.384550;,
  0.652732;0.652734;-0.384550;,
  0.923104;0.000000;-0.384552;,
  0.652732;-0.652734;-0.384551;,
  -0.000001;-0.923104;-0.384550;,
  -0.652733;-0.652733;-0.384551;,
  -0.923104;0.000000;-0.384552;,
  -0.652733;0.652733;-0.384550;,
  -0.000001;0.669329;-0.742966;,
  0.473286;0.473287;-0.742967;,
  0.669328;0.000000;-0.742967;,
  0.473287;-0.473288;-0.742966;,
  -0.000002;-0.669330;-0.742965;,
  -0.473288;-0.473286;-0.742966;,
  -0.669328;-0.000000;-0.742967;,
  -0.473287;0.473287;-0.742967;,
  -0.000001;0.337301;-0.941397;,
  0.238508;0.238507;-0.941397;,
  0.337301;0.000001;-0.941397;,
  0.238507;-0.238507;-0.941397;,
  -0.000002;-0.337301;-0.941397;,
  -0.238510;-0.238507;-0.941397;,
  -0.337303;-0.000000;-0.941396;,
  -0.238509;0.238507;-0.941397;,
  -0.000001;0.000000;-1.000000;;
  64;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;;
 }
 MeshTextureCoords {
  58;
  -0.014690;0.717320;,
  0.011320;0.723490;,
  -0.014640;0.723340;,
  0.022090;0.724300;,
  0.011340;0.725300;,
  -0.014620;0.725900;,
  -0.040590;0.725760;,
  -0.051350;0.724940;,
  -0.040600;0.723940;,
  0.033510;0.743320;,
  -0.014470;0.743040;,
  0.053390;0.744820;,
  0.033540;0.746660;,
  -0.014430;0.747780;,
  -0.062410;0.747500;,
  -0.082290;0.746000;,
  -0.062440;0.744150;,
  0.048480;0.773780;,
  -0.014210;0.773420;,
  0.074460;0.775740;,
  0.048520;0.778160;,
  -0.014150;0.779610;,
  -0.076840;0.779250;,
  -0.102820;0.777290;,
  -0.076880;0.774880;,
  0.053970;0.810250;,
  -0.013890;0.809860;,
  0.082090;0.812370;,
  0.054010;0.814990;,
  -0.013830;0.816560;,
  -0.081680;0.816170;,
  -0.109800;0.814050;,
  -0.081720;0.811440;,
  0.049120;0.847170;,
  -0.013570;0.846810;,
  0.075100;0.849130;,
  0.049160;0.851550;,
  -0.013510;0.853000;,
  -0.076200;0.852640;,
  -0.102180;0.850680;,
  -0.076240;0.848270;,
  0.034690;0.878920;,
  -0.013290;0.878650;,
  0.054580;0.880420;,
  0.034720;0.882270;,
  -0.013250;0.883380;,
  -0.061230;0.883110;,
  -0.081110;0.881610;,
  -0.061250;0.879760;,
  0.012870;0.900670;,
  -0.013100;0.900520;,
  0.023630;0.901480;,
  0.012890;0.902480;,
  -0.013070;0.903080;,
  -0.039040;0.902930;,
  -0.049800;0.902120;,
  -0.039060;0.901120;,
  -0.013020;0.909100;;
 }
}
