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
 48;
 -4.03319;-0.16046;-15.94137;,
 -1.91810;-0.16046;-15.94137;,
 -1.91810;-1.89271;-15.94137;,
 -4.03319;-1.89271;-15.94137;,
 2.02019;-0.16046;-15.94137;,
 2.02019;-1.89271;-15.94137;,
 4.13528;-0.16046;-15.94137;,
 4.13528;-1.89271;-15.94137;,
 4.13528;-0.16046;-15.94137;,
 5.95848;2.86144;-5.40570;,
 5.95848;-1.89271;-5.40570;,
 4.13528;-1.89271;-15.94137;,
 4.60894;2.33612;5.12997;,
 4.60894;-1.89271;5.12997;,
 4.60894;2.33612;5.12997;,
 2.24855;2.33612;5.12997;,
 2.24855;-1.89271;5.12997;,
 4.60894;-1.89271;5.12997;,
 -2.14646;2.33612;5.12997;,
 -2.14646;-1.89271;5.12997;,
 -4.50684;2.33612;5.12997;,
 -4.50684;-1.89271;5.12997;,
 -4.50684;2.33612;5.12997;,
 -5.85639;2.86144;-5.40570;,
 -5.85639;-1.89271;-5.40570;,
 -4.50684;-1.89271;5.12997;,
 -4.03319;-0.16046;-15.94137;,
 -4.03319;-1.89271;-15.94137;,
 -2.14646;2.33612;5.12997;,
 -1.91810;2.86144;-5.40570;,
 -5.85639;2.86144;-5.40570;,
 2.24855;2.33612;5.12997;,
 2.02019;2.86144;-5.40570;,
 5.95848;2.86144;-5.40570;,
 -1.91810;-0.16046;-15.94137;,
 -4.03319;-0.16046;-15.94137;,
 2.02019;-0.16046;-15.94137;,
 4.13528;-0.16046;-15.94137;,
 -5.85639;-1.89271;-5.40570;,
 -1.91810;-1.89271;-5.40570;,
 -2.14646;-1.89271;5.12997;,
 2.02019;-1.89271;-5.40570;,
 2.24855;-1.89271;5.12997;,
 5.95848;-1.89271;-5.40570;,
 -4.03319;-1.89271;-15.94137;,
 -1.91810;-1.89271;-15.94137;,
 2.02019;-1.89271;-15.94137;,
 4.13528;-1.89271;-15.94137;;
 
 22;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;8,9,10,11;,
 4;9,12,13,10;,
 4;14,15,16,17;,
 4;15,18,19,16;,
 4;18,20,21,19;,
 4;22,23,24,25;,
 4;23,26,27,24;,
 4;22,28,29,30;,
 4;28,31,32,29;,
 4;31,12,33,32;,
 4;30,29,34,35;,
 4;29,32,36,34;,
 4;32,33,37,36;,
 4;38,39,40,25;,
 4;39,41,42,40;,
 4;41,43,13,42;,
 4;44,45,39,38;,
 4;45,46,41,39;,
 4;46,47,43,41;;
 
 MeshMaterialList {
  2;
  22;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.119216;0.116078;0.357647;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.357647;0.282353;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  15;
  0.000000;0.000000;-1.000000;,
  0.999759;0.000000;-0.021975;,
  0.991896;0.000000;0.127055;,
  0.000000;0.000000;1.000000;,
  -0.999759;0.000000;-0.021975;,
  0.000000;0.993423;-0.114502;,
  0.000000;-1.000000;-0.000000;,
  0.985355;0.000000;-0.170516;,
  -0.991896;0.000000;0.127055;,
  -0.985355;0.000000;-0.170516;,
  0.000000;0.998759;0.049799;,
  0.000000;0.993423;-0.114502;,
  0.000000;0.998759;0.049799;,
  0.000000;0.993423;-0.114502;,
  0.000000;0.961241;-0.275709;;
  22;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;7,1,1,7;,
  4;1,2,2,1;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;8,4,4,8;,
  4;4,9,9,4;,
  4;10,10,5,11;,
  4;10,10,5,5;,
  4;10,12,13,5;,
  4;11,5,14,14;,
  4;5,5,14,14;,
  4;5,13,14,14;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;;
 }
 MeshTextureCoords {
  48;
  0.000000;0.000000;,
  0.333333;0.000000;,
  0.333333;1.000000;,
  0.000000;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333333;0.000000;,
  0.333333;1.000000;,
  0.000000;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.333333;0.000000;,
  0.333333;0.500000;,
  0.000000;0.500000;,
  0.666667;0.000000;,
  0.666667;0.500000;,
  1.000000;0.500000;,
  0.333333;1.000000;,
  0.000000;1.000000;,
  0.666667;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.333333;0.500000;,
  0.333333;1.000000;,
  0.666667;0.500000;,
  0.666667;1.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.333333;0.000000;,
  0.666667;0.000000;,
  1.000000;0.000000;;
 }
}
