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
 18;
 3.34981;18.07813;-0.00000;,
 8.00000;23.99999;-0.00000;,
 1.69124;23.99999;-0.00000;,
 1.84977;-13.40330;5.55638;,
 -2.53066;-23.99999;0.00000;,
 3.73073;-23.99999;0.00000;,
 -6.20850;-5.42398;0.00000;,
 -8.00000;3.62454;-0.00000;,
 -8.00000;-7.48917;0.00000;,
 5.99282;8.64133;-0.00000;,
 8.00000;1.47472;-0.00000;,
 8.00000;10.95515;-0.00000;,
 8.00000;-23.99999;0.00000;,
 -8.00000;23.99999;-0.00000;,
 -2.43149;10.71585;3.02947;,
 -4.78947;23.99999;-0.00000;,
 -8.00000;-23.99999;0.00000;,
 -0.69481;0.93203;-0.00000;;
 
 22;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;9,10,11;,
 3;3,5,12;,
 3;3,12,10;,
 3;13,7,14;,
 3;13,14,15;,
 3;15,14,0;,
 3;15,0,2;,
 3;8,16,4;,
 3;8,4,6;,
 3;11,1,0;,
 3;11,0,9;,
 3;6,4,3;,
 3;6,3,17;,
 3;17,14,7;,
 3;17,7,6;,
 3;17,3,10;,
 3;17,10,9;,
 3;9,0,14;,
 3;9,14,17;;
 
 MeshMaterialList {
  2;
  22;
  0,
  1,
  1,
  0,
  1,
  0,
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
  0,
  1,
  0,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\rock.jpg";
   }
  }
  Material {
   0.536471;0.536471;0.536471;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\rock.jpg;
   }
  }
 }
 MeshNormals {
  18;
  0.000000;0.000000;1.000000;,
  -0.248013;0.115390;0.961860;,
  0.368231;-0.255081;0.894058;,
  0.000000;0.000000;1.000000;,
  -0.152857;-0.080525;0.984962;,
  -0.172528;-0.158243;0.972211;,
  0.172841;0.095447;0.980314;,
  0.091258;0.059098;0.994072;,
  0.000000;0.000000;1.000000;,
  0.061039;0.158768;0.985427;,
  0.000000;-0.464383;0.885635;,
  0.039663;0.003596;0.999207;,
  -0.064512;-0.079994;0.994706;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.205808;0.033856;0.978007;,
  0.129397;-0.028331;0.991188;,
  -0.034082;0.016637;0.999281;;
  22;
  3;7,0,8;,
  3;12,5,10;,
  3;15,4,14;,
  3;16,6,13;,
  3;12,10,2;,
  3;12,2,6;,
  3;1,4,11;,
  3;1,11,9;,
  3;9,11,7;,
  3;9,7,8;,
  3;14,3,5;,
  3;14,5,15;,
  3;13,0,7;,
  3;13,7,16;,
  3;15,5,12;,
  3;15,12,17;,
  3;17,11,4;,
  3;17,4,15;,
  3;17,12,6;,
  3;17,6,16;,
  3;16,7,11;,
  3;16,11,17;;
 }
 MeshTextureCoords {
  18;
  0.290637;0.123372;,
  0.000000;0.000000;,
  0.394298;0.000000;,
  0.384389;0.779235;,
  0.658166;1.000000;,
  0.266829;1.000000;,
  0.888031;0.613000;,
  1.000000;0.424489;,
  1.000000;0.656025;,
  0.125449;0.319972;,
  0.000000;0.469277;,
  0.000000;0.271768;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.651968;0.276753;,
  0.799342;0.000000;,
  1.000000;1.000000;,
  0.543426;0.480583;;
 }
}
