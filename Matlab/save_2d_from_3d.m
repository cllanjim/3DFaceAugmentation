width = 640;
height = 480;

model = '../Dataset/Faces/Models/000001/Model_002/3DScan.obj';
output_dir = '../Dataset/Faces/Models/000001/Model_002/';
output = strcat(output_dir , '000001.jpg');

[refDepth, refRendered, refUnproject, outA, outR, outT] = renderer(width, height, model, 0, 0, 0, -90, 0, 0, 'xyz');
figure, imshow(refRendered);

mkdir(output_dir)
imwrite(refRendered, output)