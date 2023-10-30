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
 352;
 0.00000;11.60269;-0.03831;,
 -1.37731;11.34541;1.33900;,
 0.00000;11.34541;1.90950;,
 0.00000;11.60269;-0.03831;,
 -1.94782;11.34541;-0.03831;,
 0.00000;11.60269;-0.03831;,
 -1.37731;11.34541;-1.41563;,
 0.00000;11.60269;-0.03831;,
 0.00000;11.34541;-1.98613;,
 0.00000;11.60269;-0.03831;,
 1.37731;11.34541;-1.41563;,
 0.00000;11.60269;-0.03831;,
 1.94782;11.34541;-0.03831;,
 0.00000;11.60269;-0.03831;,
 1.37731;11.34541;1.33900;,
 0.00000;11.60269;-0.03831;,
 0.00000;11.34541;1.90950;,
 -2.64304;11.06721;2.60473;,
 0.00000;11.06721;3.69952;,
 -3.73783;11.06721;-0.03831;,
 -2.64304;11.06721;-2.68136;,
 0.00000;11.06721;-3.77614;,
 2.64304;11.06721;-2.68136;,
 3.73783;11.06721;-0.03831;,
 2.64304;11.06721;2.60473;,
 0.00000;11.06721;3.69952;,
 -4.04169;9.77855;3.65634;,
 0.00000;9.77855;5.18672;,
 -5.71581;9.77855;-0.03831;,
 -4.04169;9.77855;-3.73297;,
 0.00000;9.77855;-5.26334;,
 4.04169;9.77855;-3.73297;,
 5.71581;9.77855;-0.03831;,
 4.04169;9.77855;3.65634;,
 0.00000;9.77855;5.18672;,
 -4.86464;8.12310;4.40863;,
 0.00000;8.12310;6.25061;,
 -6.87964;8.12310;-0.03831;,
 -4.86464;8.12310;-4.48526;,
 0.00000;8.12310;-6.32724;,
 4.86464;8.12310;-4.48526;,
 6.87964;8.12310;-0.03831;,
 4.86464;8.12310;4.40863;,
 0.00000;8.12310;6.25061;,
 -5.29348;6.23495;4.80065;,
 0.00000;6.23495;6.80502;,
 -7.48612;6.23495;-0.03831;,
 -5.29348;6.23495;-4.87728;,
 0.00000;6.23495;-6.88164;,
 5.29349;6.23495;-4.87728;,
 7.48612;6.23495;-0.03831;,
 5.29349;6.23495;4.80065;,
 0.00000;6.23495;6.80502;,
 -5.29348;4.26711;4.80065;,
 0.00000;4.26711;6.80502;,
 -7.48612;4.26711;-0.03831;,
 -5.29348;4.26711;-4.87728;,
 0.00000;4.26711;-6.88164;,
 5.29349;4.26711;-4.87728;,
 7.48612;4.26711;-0.03831;,
 5.29349;4.26711;4.80065;,
 0.00000;4.26711;6.80502;,
 -5.53819;2.49568;5.02435;,
 0.00000;2.49568;7.12138;,
 -7.83219;2.49568;-0.03831;,
 -5.53819;2.49568;-5.10098;,
 0.00000;2.49568;-7.19800;,
 5.53819;2.49568;-5.10098;,
 7.83219;2.49568;-0.03831;,
 5.53819;2.49568;5.02435;,
 0.00000;2.49568;7.12138;,
 -4.60130;1.17303;4.16790;,
 0.00000;1.17303;5.91017;,
 -6.50721;1.17303;-0.03831;,
 -4.60130;1.17303;-4.24453;,
 0.00000;1.17303;-5.98679;,
 4.60130;1.17303;-4.24452;,
 6.50721;1.17303;-0.03831;,
 4.60130;1.17303;4.16790;,
 0.00000;1.17303;5.91017;,
 -3.29163;0.14344;2.97069;,
 0.00000;0.14344;4.21705;,
 -4.65507;0.14344;-0.03831;,
 -3.29163;0.14344;-3.04731;,
 0.00000;0.14344;-4.29368;,
 3.29163;0.14344;-3.04731;,
 4.65507;0.14344;-0.03831;,
 3.29163;0.14344;2.97069;,
 0.00000;0.14344;4.21705;,
 -1.56802;0.13254;1.52970;,
 0.00000;0.13254;2.17920;,
 -2.21751;0.13254;-0.03831;,
 -1.56802;0.13254;-1.60633;,
 0.00000;0.13254;-2.25582;,
 1.56802;0.13254;-1.60633;,
 2.21751;0.13254;-0.03831;,
 1.56802;0.13254;1.52970;,
 0.00000;0.13254;2.17920;,
 0.00000;0.05931;-0.03831;,
 0.00000;0.05931;-0.03831;,
 0.00000;0.05931;-0.03831;,
 0.00000;0.05931;-0.03831;,
 0.00000;0.05931;-0.03831;,
 0.00000;0.05931;-0.03831;,
 0.00000;0.05931;-0.03831;,
 0.00000;0.05931;-0.03831;,
 0.00000;-0.23848;3.67806;,
 -1.09845;-0.57923;3.14319;,
 -1.09845;-2.38544;4.29089;,
 0.00000;-2.04468;4.82575;,
 -1.09845;-1.26073;2.07345;,
 -1.09845;-3.06693;3.22115;,
 0.00000;-1.60148;1.53858;,
 0.00000;-3.40767;2.68628;,
 1.09845;-1.26073;2.07345;,
 1.09845;-3.06693;3.22115;,
 1.09845;-0.57923;3.14319;,
 1.09845;-2.38544;4.29089;,
 0.00000;-0.23848;3.67806;,
 0.00000;-2.04468;4.82575;,
 0.00000;-3.85742;6.65021;,
 -1.03463;-4.45476;6.65021;,
 -0.89602;-4.53479;7.24756;,
 0.00000;-4.01748;7.24756;,
 -1.03463;-5.64945;6.65021;,
 -0.89602;-5.56942;7.24756;,
 0.00000;-6.24680;6.65021;,
 0.00000;-6.08673;7.24756;,
 1.03463;-5.64945;6.65021;,
 0.89602;-5.56942;7.24756;,
 1.03463;-4.45476;6.65021;,
 0.89602;-4.53479;7.24756;,
 0.00000;-3.85742;6.65021;,
 0.00000;-4.01748;7.24756;,
 -0.51732;-4.75344;7.68485;,
 0.00000;-4.45476;7.68485;,
 -0.51732;-5.35078;7.68485;,
 0.00000;-5.64945;7.68485;,
 0.51732;-5.35078;7.68485;,
 0.51732;-4.75344;7.68485;,
 0.00000;-4.45476;7.68485;,
 0.00000;-5.05210;7.84491;,
 0.00000;-5.05210;7.84491;,
 0.00000;-5.05210;7.84491;,
 0.00000;-5.05210;7.84491;,
 0.00000;-5.05210;7.84491;,
 0.00000;-5.05210;7.84491;,
 4.34239;-0.23848;1.68726;,
 3.18746;-0.57923;2.08577;,
 3.99901;-2.38544;2.89732;,
 5.15393;-2.04468;2.49881;,
 2.43104;-1.26073;1.32935;,
 3.24259;-3.06693;2.14090;,
 2.82955;-1.60148;0.17442;,
 3.64110;-3.40767;0.98597;,
 3.98448;-1.26073;-0.22409;,
 4.79603;-3.06693;0.58746;,
 4.74090;-0.57923;0.53233;,
 5.55244;-2.38544;1.34388;,
 4.34239;-0.23848;1.68726;,
 5.15393;-2.04468;2.49881;,
 6.44402;-3.85742;3.78890;,
 5.71242;-4.45476;4.52049;,
 6.23283;-4.53479;4.84487;,
 6.86640;-4.01748;4.21128;,
 5.71242;-5.64945;4.52049;,
 6.23283;-5.56942;4.84487;,
 6.44402;-6.24680;3.78890;,
 6.86640;-6.08673;4.21128;,
 7.17562;-5.64945;3.05730;,
 7.49999;-5.56942;3.57770;,
 7.17562;-4.45476;3.05730;,
 7.49999;-4.53479;3.57770;,
 6.44402;-3.85742;3.78890;,
 6.86640;-4.01748;4.21128;,
 6.80982;-4.75344;4.88629;,
 7.17562;-4.45476;4.52049;,
 6.80982;-5.35078;4.88629;,
 7.17562;-5.64945;4.52049;,
 7.54141;-5.35078;4.15469;,
 7.54141;-4.75344;4.15469;,
 7.17562;-4.45476;4.52049;,
 7.28880;-5.05210;4.63368;,
 7.28880;-5.05210;4.63368;,
 7.28880;-5.05210;4.63368;,
 7.28880;-5.05210;4.63368;,
 7.28880;-5.05210;4.63368;,
 7.28880;-5.05210;4.63368;,
 -4.42757;-0.23848;1.98518;,
 -4.82608;-0.57923;0.83026;,
 -5.63763;-2.38544;1.64181;,
 -5.23912;-2.04468;2.79674;,
 -4.06966;-1.26073;0.07384;,
 -4.88121;-3.06693;0.88539;,
 -2.91473;-1.60148;0.47235;,
 -3.72628;-3.40767;1.28390;,
 -2.51622;-1.26073;1.62728;,
 -3.32777;-3.06693;2.43882;,
 -3.27264;-0.57923;2.38370;,
 -4.08419;-2.38544;3.19524;,
 -4.42757;-0.23848;1.98518;,
 -5.23912;-2.04468;2.79674;,
 -6.52921;-3.85742;4.08682;,
 -7.26080;-4.45476;3.35522;,
 -7.58518;-4.53479;3.87563;,
 -6.95159;-4.01748;4.50921;,
 -7.26080;-5.64945;3.35522;,
 -7.58518;-5.56942;3.87563;,
 -6.52921;-6.24680;4.08682;,
 -6.95159;-6.08673;4.50921;,
 -5.79761;-5.64945;4.81842;,
 -6.31801;-5.56942;5.14279;,
 -5.79761;-4.45476;4.81842;,
 -6.31801;-4.53479;5.14279;,
 -6.52921;-3.85742;4.08682;,
 -6.95159;-4.01748;4.50921;,
 -7.62660;-4.75344;4.45262;,
 -7.26080;-4.45476;4.81842;,
 -7.62660;-5.35078;4.45262;,
 -7.26080;-5.64945;4.81842;,
 -6.89501;-5.35078;5.18421;,
 -6.89501;-4.75344;5.18421;,
 -7.26080;-4.45476;4.81842;,
 -7.37398;-5.05210;4.93160;,
 -7.37398;-5.05210;4.93160;,
 -7.37398;-5.05210;4.93160;,
 -7.37398;-5.05210;4.93160;,
 -7.37398;-5.05210;4.93160;,
 -7.37398;-5.05210;4.93160;,
 0.00000;-0.23848;-3.92633;,
 1.09845;-0.57923;-3.39146;,
 1.09845;-2.38544;-4.53917;,
 -0.00000;-2.04468;-5.07404;,
 1.09845;-1.26073;-2.32172;,
 1.09845;-3.06693;-3.46943;,
 0.00000;-1.60148;-1.78685;,
 0.00000;-3.40767;-2.93456;,
 -1.09845;-1.26073;-2.32173;,
 -1.09845;-3.06693;-3.46943;,
 -1.09845;-0.57923;-3.39146;,
 -1.09845;-2.38544;-4.53917;,
 0.00000;-0.23848;-3.92633;,
 -0.00000;-2.04468;-5.07404;,
 -0.00000;-3.85742;-6.89849;,
 1.03463;-4.45476;-6.89849;,
 0.89602;-4.53479;-7.49584;,
 -0.00000;-4.01748;-7.49584;,
 1.03463;-5.64945;-6.89849;,
 0.89602;-5.56942;-7.49584;,
 -0.00000;-6.24680;-6.89849;,
 -0.00000;-6.08673;-7.49584;,
 -1.03463;-5.64945;-6.89849;,
 -0.89602;-5.56942;-7.49584;,
 -1.03463;-4.45476;-6.89849;,
 -0.89602;-4.53479;-7.49584;,
 -0.00000;-3.85742;-6.89849;,
 -0.00000;-4.01748;-7.49584;,
 0.51732;-4.75344;-7.93313;,
 -0.00000;-4.45476;-7.93313;,
 0.51732;-5.35078;-7.93313;,
 -0.00000;-5.64945;-7.93313;,
 -0.51732;-5.35078;-7.93313;,
 -0.51732;-4.75344;-7.93313;,
 -0.00000;-4.45476;-7.93313;,
 -0.00000;-5.05210;-8.09319;,
 -0.00000;-5.05210;-8.09319;,
 -0.00000;-5.05210;-8.09319;,
 -0.00000;-5.05210;-8.09319;,
 -0.00000;-5.05210;-8.09319;,
 -0.00000;-5.05210;-8.09319;,
 -4.06252;-0.23848;-2.51141;,
 -2.90759;-0.57923;-2.90992;,
 -3.71914;-2.38544;-3.72147;,
 -4.87406;-2.04468;-3.32296;,
 -2.15116;-1.26073;-2.15350;,
 -2.96271;-3.06693;-2.96505;,
 -2.54967;-1.60148;-0.99857;,
 -3.36122;-3.40767;-1.81012;,
 -3.70461;-1.26073;-0.60006;,
 -4.51615;-3.06693;-1.41161;,
 -4.46103;-0.57923;-1.35648;,
 -5.27257;-2.38544;-2.16803;,
 -4.06252;-0.23848;-2.51141;,
 -4.87406;-2.04468;-3.32296;,
 -6.16415;-3.85742;-4.61305;,
 -5.43255;-4.45476;-5.34464;,
 -5.95296;-4.53479;-5.66902;,
 -6.58654;-4.01748;-5.03543;,
 -5.43255;-5.64945;-5.34464;,
 -5.95296;-5.56942;-5.66902;,
 -6.16415;-6.24680;-4.61305;,
 -6.58654;-6.08673;-5.03543;,
 -6.89575;-5.64945;-3.88145;,
 -7.22012;-5.56942;-4.40185;,
 -6.89575;-4.45476;-3.88145;,
 -7.22012;-4.53479;-4.40185;,
 -6.16415;-3.85742;-4.61305;,
 -6.58654;-4.01748;-5.03543;,
 -6.52995;-4.75344;-5.71044;,
 -6.89575;-4.45476;-5.34464;,
 -6.52995;-5.35078;-5.71044;,
 -6.89575;-5.64945;-5.34464;,
 -7.26155;-5.35078;-4.97884;,
 -7.26155;-4.75344;-4.97884;,
 -6.89575;-4.45476;-5.34464;,
 -7.00893;-5.05210;-5.45782;,
 -7.00893;-5.05210;-5.45782;,
 -7.00893;-5.05210;-5.45782;,
 -7.00893;-5.05210;-5.45782;,
 -7.00893;-5.05210;-5.45782;,
 -7.00893;-5.05210;-5.45782;,
 3.86046;-0.12792;-2.33999;,
 4.25897;-0.46867;-1.18506;,
 5.07052;-2.27487;-1.99661;,
 4.67201;-1.93412;-3.15154;,
 3.50255;-1.15017;-0.42864;,
 4.31410;-2.95637;-1.24019;,
 2.34762;-1.49092;-0.82715;,
 3.15917;-3.29711;-1.63870;,
 1.94911;-1.15017;-1.98208;,
 2.76066;-2.95637;-2.79363;,
 2.70553;-0.46867;-2.73851;,
 3.51708;-2.27487;-3.55005;,
 3.86046;-0.12792;-2.33999;,
 4.67201;-1.93412;-3.15154;,
 5.96210;-3.74685;-4.44163;,
 6.69369;-4.34420;-3.71003;,
 7.01806;-4.42423;-4.23043;,
 6.38448;-3.90692;-4.86401;,
 6.69369;-5.53890;-3.71003;,
 7.01806;-5.45887;-4.23043;,
 5.96210;-6.13624;-4.44163;,
 6.38448;-5.97618;-4.86401;,
 5.23050;-5.53890;-5.17322;,
 5.75090;-5.45887;-5.49760;,
 5.23050;-4.34420;-5.17322;,
 5.75090;-4.42423;-5.49760;,
 5.96210;-3.74685;-4.44163;,
 6.38448;-3.90692;-4.86401;,
 7.05949;-4.64289;-4.80743;,
 6.69369;-4.34420;-5.17322;,
 7.05949;-5.24021;-4.80743;,
 6.69369;-5.53890;-5.17322;,
 6.32789;-5.24021;-5.53903;,
 6.32789;-4.64289;-5.53903;,
 6.69369;-4.34420;-5.17322;,
 6.80687;-4.94156;-5.28641;,
 6.80687;-4.94156;-5.28641;,
 6.80687;-4.94156;-5.28641;,
 6.80687;-4.94156;-5.28641;,
 6.80687;-4.94156;-5.28641;,
 6.80687;-4.94156;-5.28641;;
 
 232;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 4;63,62,71,72;,
 4;62,64,73,71;,
 4;64,65,74,73;,
 4;65,66,75,74;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;68,69,78,77;,
 4;69,70,79,78;,
 4;72,71,80,81;,
 4;71,73,82,80;,
 4;73,74,83,82;,
 4;74,75,84,83;,
 4;75,76,85,84;,
 4;76,77,86,85;,
 4;77,78,87,86;,
 4;78,79,88,87;,
 4;81,80,89,90;,
 4;80,82,91,89;,
 4;82,83,92,91;,
 4;83,84,93,92;,
 4;84,85,94,93;,
 4;85,86,95,94;,
 4;86,87,96,95;,
 4;87,88,97,96;,
 3;90,89,98;,
 3;89,91,99;,
 3;91,92,100;,
 3;92,93,101;,
 3;93,94,102;,
 3;94,95,103;,
 3;95,96,104;,
 3;96,97,105;,
 4;106,107,108,109;,
 4;107,110,111,108;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 4;120,121,122,123;,
 4;121,124,125,122;,
 4;124,126,127,125;,
 4;126,128,129,127;,
 4;128,130,131,129;,
 4;130,132,133,131;,
 4;123,122,134,135;,
 4;122,125,136,134;,
 4;125,127,137,136;,
 4;127,129,138,137;,
 4;129,131,139,138;,
 4;131,133,140,139;,
 3;135,134,141;,
 3;134,136,142;,
 3;136,137,143;,
 3;137,138,144;,
 3;138,139,145;,
 3;139,140,146;,
 4;147,148,149,150;,
 4;148,151,152,149;,
 4;151,153,154,152;,
 4;153,155,156,154;,
 4;155,157,158,156;,
 4;157,159,160,158;,
 4;161,162,163,164;,
 4;162,165,166,163;,
 4;165,167,168,166;,
 4;167,169,170,168;,
 4;169,171,172,170;,
 4;171,173,174,172;,
 4;164,163,175,176;,
 4;163,166,177,175;,
 4;166,168,178,177;,
 4;168,170,179,178;,
 4;170,172,180,179;,
 4;172,174,181,180;,
 3;176,175,182;,
 3;175,177,183;,
 3;177,178,184;,
 3;178,179,185;,
 3;179,180,186;,
 3;180,181,187;,
 4;188,189,190,191;,
 4;189,192,193,190;,
 4;192,194,195,193;,
 4;194,196,197,195;,
 4;196,198,199,197;,
 4;198,200,201,199;,
 4;202,203,204,205;,
 4;203,206,207,204;,
 4;206,208,209,207;,
 4;208,210,211,209;,
 4;210,212,213,211;,
 4;212,214,215,213;,
 4;205,204,216,217;,
 4;204,207,218,216;,
 4;207,209,219,218;,
 4;209,211,220,219;,
 4;211,213,221,220;,
 4;213,215,222,221;,
 3;217,216,223;,
 3;216,218,224;,
 3;218,219,225;,
 3;219,220,226;,
 3;220,221,227;,
 3;221,222,228;,
 4;229,230,231,232;,
 4;230,233,234,231;,
 4;233,235,236,234;,
 4;235,237,238,236;,
 4;237,239,240,238;,
 4;239,241,242,240;,
 4;243,244,245,246;,
 4;244,247,248,245;,
 4;247,249,250,248;,
 4;249,251,252,250;,
 4;251,253,254,252;,
 4;253,255,256,254;,
 4;246,245,257,258;,
 4;245,248,259,257;,
 4;248,250,260,259;,
 4;250,252,261,260;,
 4;252,254,262,261;,
 4;254,256,263,262;,
 3;258,257,264;,
 3;257,259,265;,
 3;259,260,266;,
 3;260,261,267;,
 3;261,262,268;,
 3;262,263,269;,
 4;270,271,272,273;,
 4;271,274,275,272;,
 4;274,276,277,275;,
 4;276,278,279,277;,
 4;278,280,281,279;,
 4;280,282,283,281;,
 4;284,285,286,287;,
 4;285,288,289,286;,
 4;288,290,291,289;,
 4;290,292,293,291;,
 4;292,294,295,293;,
 4;294,296,297,295;,
 4;287,286,298,299;,
 4;286,289,300,298;,
 4;289,291,301,300;,
 4;291,293,302,301;,
 4;293,295,303,302;,
 4;295,297,304,303;,
 3;299,298,305;,
 3;298,300,306;,
 3;300,301,307;,
 3;301,302,308;,
 3;302,303,309;,
 3;303,304,310;,
 4;311,312,313,314;,
 4;312,315,316,313;,
 4;315,317,318,316;,
 4;317,319,320,318;,
 4;319,321,322,320;,
 4;321,323,324,322;,
 4;325,326,327,328;,
 4;326,329,330,327;,
 4;329,331,332,330;,
 4;331,333,334,332;,
 4;333,335,336,334;,
 4;335,337,338,336;,
 4;328,327,339,340;,
 4;327,330,341,339;,
 4;330,332,342,341;,
 4;332,334,343,342;,
 4;334,336,344,343;,
 4;336,338,345,344;,
 3;340,339,346;,
 3;339,341,347;,
 3;341,342,348;,
 3;342,343,349;,
 3;343,344,350;,
 3;344,345,351;;
 
 MeshMaterialList {
  1;
  232;
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
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  232;
  0.000000;1.000000;0.000000;,
  0.000000;0.989828;0.142268;,
  -0.100599;0.989828;0.100599;,
  -0.142268;0.989828;0.000000;,
  -0.100598;0.989828;-0.100599;,
  0.000000;0.989828;-0.142268;,
  0.100598;0.989828;-0.100599;,
  0.142268;0.989828;0.000000;,
  0.100599;0.989828;0.100599;,
  0.000000;0.912111;0.409944;,
  -0.264364;0.922269;0.282014;,
  -0.363096;0.931752;0.000000;,
  -0.264364;0.922269;-0.282014;,
  0.000000;0.912111;-0.409944;,
  0.264364;0.922269;-0.282014;,
  0.363096;0.931752;0.000000;,
  0.264364;0.922269;0.282014;,
  0.000000;0.661521;0.749926;,
  -0.493079;0.688593;0.531707;,
  -0.698441;0.715667;0.000000;,
  -0.493078;0.688594;-0.531707;,
  0.000000;0.661522;-0.749926;,
  0.493078;0.688594;-0.531707;,
  0.698441;0.715668;0.000000;,
  0.493079;0.688593;0.531707;,
  -0.000000;0.416308;0.909224;,
  -0.615994;0.431093;0.659326;,
  -0.894552;0.446964;0.000000;,
  -0.615993;0.431093;-0.659326;,
  -0.000000;0.416307;-0.909224;,
  0.615993;0.431094;-0.659326;,
  0.894551;0.446965;0.000000;,
  0.615993;0.431093;0.659326;,
  -0.000000;0.142669;0.989770;,
  -0.676352;0.148756;0.721401;,
  -0.987853;0.155393;0.000000;,
  -0.676352;0.148756;-0.721401;,
  -0.000000;0.142668;-0.989771;,
  0.676352;0.148757;-0.721401;,
  0.987853;0.155394;0.000000;,
  0.676352;0.148757;0.721401;,
  -0.000000;0.088334;0.996091;,
  -0.681258;0.092226;0.726211;,
  -0.995336;0.096468;0.000000;,
  -0.681257;0.092226;-0.726211;,
  -0.000000;0.088334;-0.996091;,
  0.681258;0.092225;-0.726211;,
  0.995336;0.096467;0.000000;,
  0.681258;0.092225;0.726211;,
  -0.000000;-0.285144;0.958485;,
  -0.652284;-0.293538;0.698828;,
  -0.953029;-0.302880;0.000000;,
  -0.652284;-0.293538;-0.698829;,
  -0.000000;-0.285144;-0.958485;,
  0.652283;-0.293540;-0.698828;,
  0.953028;-0.302882;0.000000;,
  0.652284;-0.293539;0.698828;,
  0.000000;-0.773448;0.633859;,
  -0.419515;-0.786306;0.453575;,
  -0.600548;-0.799589;0.000000;,
  -0.419515;-0.786306;-0.453575;,
  0.000000;-0.773448;-0.633859;,
  0.419515;-0.786307;-0.453574;,
  0.600548;-0.799589;0.000000;,
  0.419515;-0.786306;0.453575;,
  0.000000;-0.962927;0.269763;,
  -0.176304;-0.965541;0.191434;,
  -0.250229;-0.968187;-0.000005;,
  -0.176318;-0.965538;-0.191438;,
  0.000000;-0.962927;-0.269763;,
  0.176318;-0.965538;-0.191439;,
  0.250229;-0.968186;-0.000005;,
  0.176304;-0.965541;0.191434;,
  0.000000;-0.999817;0.019106;,
  -0.013317;-0.999821;0.013462;,
  -0.018782;-0.999824;-0.000005;,
  -0.013331;-0.999820;-0.013467;,
  -0.000000;-0.999817;-0.019106;,
  0.013331;-0.999820;-0.013467;,
  0.018782;-0.999824;-0.000005;,
  0.013317;-0.999821;0.013462;,
  -0.000000;-1.000000;0.000000;,
  -0.499998;0.464456;0.730946;,
  -1.000000;0.000000;0.000000;,
  -0.499998;-0.464460;-0.730944;,
  0.499998;-0.464460;-0.730944;,
  1.000000;0.000000;0.000000;,
  0.499998;0.464456;0.730946;,
  0.000000;0.965927;0.258816;,
  -0.836517;0.482965;0.258813;,
  -0.836517;-0.482963;0.258817;,
  0.000000;-0.965925;0.258824;,
  0.836517;-0.482963;0.258817;,
  0.836517;0.482965;0.258813;,
  0.000000;0.862095;0.506747;,
  -0.746597;0.431048;0.506745;,
  -0.746596;-0.431049;0.506745;,
  0.000000;-0.862095;0.506746;,
  0.746596;-0.431049;0.506745;,
  0.746597;0.431048;0.506745;,
  0.000000;0.492325;0.870412;,
  -0.426366;0.246162;0.870411;,
  -0.426364;-0.246164;0.870412;,
  0.000000;-0.492327;0.870410;,
  0.426364;-0.246164;0.870412;,
  0.426366;0.246162;0.870411;,
  0.000000;0.000001;1.000000;,
  0.163301;0.464458;0.870409;,
  -0.707107;0.000000;0.707107;,
  -0.870407;-0.464461;-0.163303;,
  -0.163303;-0.464461;-0.870407;,
  0.707109;0.000000;-0.707104;,
  0.870411;0.464455;0.163302;,
  0.183013;0.965925;0.183015;,
  -0.408494;0.482965;0.774517;,
  -0.408492;-0.482963;0.774520;,
  0.183018;-0.965923;0.183021;,
  0.774522;-0.482963;-0.408487;,
  0.774520;0.482966;-0.408490;,
  0.358328;0.862092;0.358326;,
  -0.169592;0.431048;0.886248;,
  -0.169592;-0.431049;0.886248;,
  0.358327;-0.862094;0.358324;,
  0.886248;-0.431049;-0.169593;,
  0.886249;0.431047;-0.169591;,
  0.615476;0.492329;0.615469;,
  0.313986;0.246165;0.916960;,
  0.313987;-0.246166;0.916959;,
  0.615475;-0.492332;0.615467;,
  0.916962;-0.246165;0.313979;,
  0.916963;0.246163;0.313979;,
  0.707111;0.000001;0.707103;,
  -0.870409;0.464459;0.163301;,
  -0.707107;0.000000;-0.707107;,
  0.163303;-0.464461;-0.870407;,
  0.870407;-0.464461;-0.163303;,
  0.707106;-0.000003;0.707108;,
  -0.163300;0.464458;0.870409;,
  -0.183013;0.965926;0.183013;,
  -0.774518;0.482965;-0.408493;,
  -0.774521;-0.482963;-0.408490;,
  -0.183019;-0.965923;0.183020;,
  0.408490;-0.482963;0.774521;,
  0.408492;0.482965;0.774518;,
  -0.358325;0.862093;0.358328;,
  -0.886248;0.431048;-0.169593;,
  -0.886248;-0.431048;-0.169591;,
  -0.358325;-0.862093;0.358329;,
  0.169592;-0.431047;0.886249;,
  0.169592;0.431046;0.886249;,
  -0.615473;0.492324;0.615476;,
  -0.916959;0.246163;0.313991;,
  -0.916958;-0.246163;0.313994;,
  -0.615471;-0.492325;0.615476;,
  -0.313989;-0.246162;0.916960;,
  -0.313988;0.246160;0.916961;,
  -0.707105;0.000001;0.707109;,
  0.500001;0.464460;-0.730942;,
  1.000000;0.000000;0.000000;,
  0.499998;-0.464463;0.730942;,
  -0.500000;-0.464460;0.730942;,
  -1.000000;0.000000;0.000000;,
  -0.500001;0.464460;-0.730942;,
  0.000000;0.965926;-0.258817;,
  0.836517;0.482965;-0.258814;,
  0.836517;-0.482963;-0.258817;,
  -0.000000;-0.965924;-0.258824;,
  -0.836517;-0.482963;-0.258817;,
  -0.836517;0.482965;-0.258814;,
  0.000000;0.862095;-0.506747;,
  0.746597;0.431048;-0.506745;,
  0.746596;-0.431049;-0.506745;,
  -0.000000;-0.862095;-0.506746;,
  -0.746596;-0.431049;-0.506745;,
  -0.746597;0.431048;-0.506745;,
  0.000000;0.492325;-0.870411;,
  0.426367;0.246163;-0.870411;,
  0.426365;-0.246164;-0.870412;,
  -0.000000;-0.492328;-0.870410;,
  -0.426365;-0.246164;-0.870412;,
  -0.426367;0.246163;-0.870411;,
  0.000000;0.000001;-1.000000;,
  -0.163301;0.464458;-0.870409;,
  0.707103;0.000003;-0.707110;,
  0.870407;-0.464461;0.163303;,
  0.163302;-0.464460;0.870407;,
  -0.707108;-0.000003;0.707106;,
  -0.870410;0.464455;-0.163302;,
  -0.183013;0.965926;-0.183013;,
  0.408494;0.482965;-0.774518;,
  0.408491;-0.482963;-0.774521;,
  -0.183020;-0.965923;-0.183019;,
  -0.774521;-0.482963;0.408490;,
  -0.774518;0.482965;0.408492;,
  -0.358328;0.862093;-0.358325;,
  0.169592;0.431048;-0.886249;,
  0.169591;-0.431049;-0.886248;,
  -0.358327;-0.862094;-0.358325;,
  -0.886247;-0.431049;0.169598;,
  -0.886247;0.431048;0.169598;,
  -0.615475;0.492324;-0.615473;,
  -0.313992;0.246162;-0.916959;,
  -0.313993;-0.246163;-0.916958;,
  -0.615474;-0.492327;-0.615472;,
  -0.916960;-0.246164;-0.313988;,
  -0.916960;0.246163;-0.313986;,
  -0.707107;0.000001;-0.707107;,
  0.870408;0.464460;-0.163301;,
  0.707107;0.000000;0.707107;,
  -0.163303;-0.464461;0.870407;,
  -0.870407;-0.464461;0.163303;,
  -0.707108;-0.000003;-0.707106;,
  0.163305;0.464459;-0.870408;,
  0.183021;0.965923;-0.183019;,
  0.774522;0.482961;0.408489;,
  0.774520;-0.482964;0.408491;,
  0.183015;-0.965925;-0.183013;,
  -0.408499;-0.482966;-0.774515;,
  -0.408496;0.482963;-0.774517;,
  0.358332;0.862090;-0.358329;,
  0.886250;0.431044;0.169595;,
  0.886248;-0.431046;0.169598;,
  0.358328;-0.862094;-0.358324;,
  -0.169600;-0.431049;-0.886246;,
  -0.169598;0.431047;-0.886248;,
  0.615476;0.492324;-0.615472;,
  0.916960;0.246162;-0.313988;,
  0.916960;-0.246165;-0.313985;,
  0.615473;-0.492331;-0.615470;,
  0.313987;-0.246167;-0.916959;,
  0.313990;0.246164;-0.916959;,
  0.707107;-0.000003;-0.707106;;
  232;
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
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  3;73,74,81;,
  3;74,75,81;,
  3;75,76,81;,
  3;76,77,81;,
  3;77,78,81;,
  3;78,79,81;,
  3;79,80,81;,
  3;80,73,81;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;84,84,84,84;,
  4;85,85,85,85;,
  4;86,86,86,86;,
  4;87,87,87,87;,
  4;88,89,95,94;,
  4;89,90,96,95;,
  4;90,91,97,96;,
  4;91,92,98,97;,
  4;92,93,99,98;,
  4;93,88,94,99;,
  4;94,95,101,100;,
  4;95,96,102,101;,
  4;96,97,103,102;,
  4;97,98,104,103;,
  4;98,99,105,104;,
  4;99,94,100,105;,
  3;100,101,106;,
  3;101,102,106;,
  3;102,103,106;,
  3;103,104,106;,
  3;104,105,106;,
  3;105,100,106;,
  4;107,107,107,107;,
  4;108,108,108,108;,
  4;109,109,109,109;,
  4;110,110,110,110;,
  4;111,111,111,111;,
  4;112,112,112,112;,
  4;113,114,120,119;,
  4;114,115,121,120;,
  4;115,116,122,121;,
  4;116,117,123,122;,
  4;117,118,124,123;,
  4;118,113,119,124;,
  4;119,120,126,125;,
  4;120,121,127,126;,
  4;121,122,128,127;,
  4;122,123,129,128;,
  4;123,124,130,129;,
  4;124,119,125,130;,
  3;125,126,131;,
  3;126,127,131;,
  3;127,128,131;,
  3;128,129,131;,
  3;129,130,131;,
  3;130,125,131;,
  4;132,132,132,132;,
  4;133,133,133,133;,
  4;134,134,134,134;,
  4;135,135,135,135;,
  4;136,136,136,136;,
  4;137,137,137,137;,
  4;138,139,145,144;,
  4;139,140,146,145;,
  4;140,141,147,146;,
  4;141,142,148,147;,
  4;142,143,149,148;,
  4;143,138,144,149;,
  4;144,145,151,150;,
  4;145,146,152,151;,
  4;146,147,153,152;,
  4;147,148,154,153;,
  4;148,149,155,154;,
  4;149,144,150,155;,
  3;150,151,156;,
  3;151,152,156;,
  3;152,153,156;,
  3;153,154,156;,
  3;154,155,156;,
  3;155,150,156;,
  4;157,157,157,157;,
  4;158,158,158,158;,
  4;159,159,159,159;,
  4;160,160,160,160;,
  4;161,161,161,161;,
  4;162,162,162,162;,
  4;163,164,170,169;,
  4;164,165,171,170;,
  4;165,166,172,171;,
  4;166,167,173,172;,
  4;167,168,174,173;,
  4;168,163,169,174;,
  4;169,170,176,175;,
  4;170,171,177,176;,
  4;171,172,178,177;,
  4;172,173,179,178;,
  4;173,174,180,179;,
  4;174,169,175,180;,
  3;175,176,181;,
  3;176,177,181;,
  3;177,178,181;,
  3;178,179,181;,
  3;179,180,181;,
  3;180,175,181;,
  4;182,182,182,182;,
  4;183,183,183,183;,
  4;184,184,184,184;,
  4;185,185,185,185;,
  4;186,186,186,186;,
  4;187,187,187,187;,
  4;188,189,195,194;,
  4;189,190,196,195;,
  4;190,191,197,196;,
  4;191,192,198,197;,
  4;192,193,199,198;,
  4;193,188,194,199;,
  4;194,195,201,200;,
  4;195,196,202,201;,
  4;196,197,203,202;,
  4;197,198,204,203;,
  4;198,199,205,204;,
  4;199,194,200,205;,
  3;200,201,206;,
  3;201,202,206;,
  3;202,203,206;,
  3;203,204,206;,
  3;204,205,206;,
  3;205,200,206;,
  4;207,207,207,207;,
  4;208,208,208,208;,
  4;209,209,209,209;,
  4;210,210,210,210;,
  4;211,211,211,211;,
  4;212,212,212,212;,
  4;213,214,220,219;,
  4;214,215,221,220;,
  4;215,216,222,221;,
  4;216,217,223,222;,
  4;217,218,224,223;,
  4;218,213,219,224;,
  4;219,220,226,225;,
  4;220,221,227,226;,
  4;221,222,228,227;,
  4;222,223,229,228;,
  4;223,224,230,229;,
  4;224,219,225,230;,
  3;225,226,231;,
  3;226,227,231;,
  3;227,228,231;,
  3;228,229,231;,
  3;229,230,231;,
  3;230,225,231;;
 }
 MeshTextureCoords {
  352;
  0.062500;0.000000;,
  0.125000;0.090910;,
  0.000000;0.090910;,
  0.187500;0.000000;,
  0.250000;0.090910;,
  0.312500;0.000000;,
  0.375000;0.090910;,
  0.437500;0.000000;,
  0.500000;0.090910;,
  0.562500;0.000000;,
  0.625000;0.090910;,
  0.687500;0.000000;,
  0.750000;0.090910;,
  0.812500;0.000000;,
  0.875000;0.090910;,
  0.937500;0.000000;,
  1.000000;0.090910;,
  0.125000;0.181820;,
  0.000000;0.181820;,
  0.250000;0.181820;,
  0.375000;0.181820;,
  0.500000;0.181820;,
  0.625000;0.181820;,
  0.750000;0.181820;,
  0.875000;0.181820;,
  1.000000;0.181820;,
  0.125000;0.272730;,
  0.000000;0.272730;,
  0.250000;0.272730;,
  0.375000;0.272730;,
  0.500000;0.272730;,
  0.625000;0.272730;,
  0.750000;0.272730;,
  0.875000;0.272730;,
  1.000000;0.272730;,
  0.125000;0.363640;,
  0.000000;0.363640;,
  0.250000;0.363640;,
  0.375000;0.363640;,
  0.500000;0.363640;,
  0.625000;0.363640;,
  0.750000;0.363640;,
  0.875000;0.363640;,
  1.000000;0.363640;,
  0.125000;0.454550;,
  0.000000;0.454550;,
  0.250000;0.454550;,
  0.375000;0.454550;,
  0.500000;0.454550;,
  0.625000;0.454550;,
  0.750000;0.454550;,
  0.875000;0.454550;,
  1.000000;0.454550;,
  0.125000;0.545450;,
  0.000000;0.545450;,
  0.250000;0.545450;,
  0.375000;0.545450;,
  0.500000;0.545450;,
  0.625000;0.545450;,
  0.750000;0.545450;,
  0.875000;0.545450;,
  1.000000;0.545450;,
  0.125000;0.636360;,
  0.000000;0.636360;,
  0.250000;0.636360;,
  0.375000;0.636360;,
  0.500000;0.636360;,
  0.625000;0.636360;,
  0.750000;0.636360;,
  0.875000;0.636360;,
  1.000000;0.636360;,
  0.125000;0.727270;,
  0.000000;0.727270;,
  0.250000;0.727270;,
  0.375000;0.727270;,
  0.500000;0.727270;,
  0.625000;0.727270;,
  0.750000;0.727270;,
  0.875000;0.727270;,
  1.000000;0.727270;,
  0.125000;0.818180;,
  0.000000;0.818180;,
  0.250000;0.818180;,
  0.375000;0.818180;,
  0.500000;0.818180;,
  0.625000;0.818180;,
  0.750000;0.818180;,
  0.875000;0.818180;,
  1.000000;0.818180;,
  0.125000;0.909090;,
  0.000000;0.909090;,
  0.250000;0.909090;,
  0.375000;0.909090;,
  0.500000;0.909090;,
  0.625000;0.909090;,
  0.750000;0.909090;,
  0.875000;0.909090;,
  1.000000;0.909090;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.500000;,
  0.333330;0.666670;,
  0.500000;0.500000;,
  0.500000;0.666670;,
  0.666670;0.500000;,
  0.666670;0.666670;,
  0.833330;0.500000;,
  0.833330;0.666670;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.500000;,
  0.333330;0.666670;,
  0.500000;0.500000;,
  0.500000;0.666670;,
  0.666670;0.500000;,
  0.666670;0.666670;,
  0.833330;0.500000;,
  0.833330;0.666670;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.500000;,
  0.333330;0.666670;,
  0.500000;0.500000;,
  0.500000;0.666670;,
  0.666670;0.500000;,
  0.666670;0.666670;,
  0.833330;0.500000;,
  0.833330;0.666670;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.500000;,
  0.333330;0.666670;,
  0.500000;0.500000;,
  0.500000;0.666670;,
  0.666670;0.500000;,
  0.666670;0.666670;,
  0.833330;0.500000;,
  0.833330;0.666670;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.500000;,
  0.333330;0.666670;,
  0.500000;0.500000;,
  0.500000;0.666670;,
  0.666670;0.500000;,
  0.666670;0.666670;,
  0.833330;0.500000;,
  0.833330;0.666670;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.500000;,
  0.333330;0.666670;,
  0.500000;0.500000;,
  0.500000;0.666670;,
  0.666670;0.500000;,
  0.666670;0.666670;,
  0.833330;0.500000;,
  0.833330;0.666670;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;;
 }
}