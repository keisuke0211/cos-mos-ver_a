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
 22;
 -3.70175;-7.99970;-0.06981;,
 7.25032;-7.99970;-0.06981;,
 2.25740;-4.34416;2.34380;,
 12.66235;2.03858;2.37886;,
 16.00000;-7.99970;-0.06981;,
 16.00000;4.08600;0.03566;,
 -13.99076;-2.20225;-0.01922;,
 -16.00000;7.99970;0.06981;,
 -16.00000;-3.59584;-0.03138;,
 -2.87459;5.50786;0.04807;,
 0.71806;7.99970;0.06981;,
 -6.17790;7.99970;0.06981;,
 -2.42807;-0.91372;-0.00797;,
 -12.84896;-7.99970;-0.06981;,
 16.00000;7.99970;0.06981;,
 10.68032;7.99970;0.06981;,
 -14.60250;7.99970;0.06981;,
 -7.14934;2.54292;1.84492;,
 -16.00000;-7.99970;-0.06981;,
 15.03175;-7.99970;-0.06981;,
 6.62999;-1.66187;-0.01450;,
 1.81418;1.97092;0.01720;;
 
 28;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;9,10,11;,
 3;0,2,12;,
 3;0,12,13;,
 3;5,14,15;,
 3;5,15,3;,
 3;16,7,6;,
 3;16,6,17;,
 3;6,13,12;,
 3;6,12,17;,
 3;8,18,13;,
 3;8,13,6;,
 3;19,4,3;,
 3;19,3,20;,
 3;20,2,1;,
 3;20,1,19;,
 3;20,3,15;,
 3;20,15,21;,
 3;21,12,2;,
 3;21,2,20;,
 3;11,16,17;,
 3;11,17,9;,
 3;9,17,12;,
 3;9,12,21;,
 3;21,15,10;,
 3;21,10,9;;
 
 MeshMaterialList {
  2;
  28;
  1,
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
  1,
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
   TextureFilename {
    "data\\TEXTUTE\\rock.jpg";
   }
  }
  Material {
   0.467451;0.467451;0.467451;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTUTE\\rock.jpg";
   }
  }
 }
 MeshNormals {
  22;
  0.000000;-0.008726;0.999962;,
  0.000000;-0.008726;0.999962;,
  0.304809;-0.128843;0.943658;,
  0.000000;-0.008726;0.999962;,
  -0.084179;0.094226;0.991986;,
  0.162512;-0.186015;0.969014;,
  -0.028178;0.124615;0.991805;,
  -0.000000;-0.008726;0.999962;,
  -0.031660;-0.006278;0.999479;,
  0.317895;0.147225;0.936626;,
  0.054202;0.021802;0.998292;,
  -0.145062;-0.175322;0.973766;,
  0.020729;0.050240;0.998522;,
  -0.034183;-0.081474;0.996089;,
  0.081549;0.031985;0.996156;,
  -0.000000;-0.008726;0.999962;,
  0.000000;-0.008726;0.999962;,
  -0.068398;-0.176330;0.981952;,
  0.070708;0.192719;0.978703;,
  0.007612;0.108947;0.994018;,
  0.011671;0.049359;0.998713;,
  0.119309;0.053099;0.991436;;
  28;
  3;11,5,12;,
  3;10,2,9;,
  3;13,1,15;,
  3;21,16,18;,
  3;11,12,8;,
  3;11,8,7;,
  3;9,0,6;,
  3;9,6,10;,
  3;4,1,13;,
  3;4,13,14;,
  3;13,7,8;,
  3;13,8,14;,
  3;15,3,7;,
  3;15,7,13;,
  3;17,2,10;,
  3;17,10,20;,
  3;20,12,5;,
  3;20,5,17;,
  3;20,10,6;,
  3;20,6,19;,
  3;19,8,12;,
  3;19,12,20;,
  3;18,4,14;,
  3;18,14,21;,
  3;21,14,8;,
  3;21,8,19;,
  3;19,6,16;,
  3;19,16,21;;
 }
 MeshTextureCoords {
  22;
  0.615680;1.000000;,
  0.273427;1.000000;,
  0.429456;0.771520;,
  0.104302;0.372584;,
  0.000000;1.000000;,
  0.000000;0.244615;,
  0.937211;0.637646;,
  1.000000;0.000000;,
  1.000000;0.724749;,
  0.589831;0.155746;,
  0.477561;0.000000;,
  0.693059;0.000000;,
  0.575877;0.557110;,
  0.901530;1.000000;,
  0.000000;0.000000;,
  0.166240;0.000000;,
  0.956328;0.000000;,
  0.723417;0.341062;,
  1.000000;1.000000;,
  0.030258;1.000000;,
  0.292813;0.603871;,
  0.443307;0.376813;;
 }
}
