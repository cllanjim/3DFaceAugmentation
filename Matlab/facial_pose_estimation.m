width = 640;
height = 480;
model_name = '3DModels/Faces/Model_2/3DScan.obj';
keypoints_file = 'features.txt';
pts3D_file = '3D_points.txt';

%% STEP 1 - RENDER 3D REFERENCE MODEL, DETECT SPECIFIC FACIAL FEATURES, GET THEIR 3D COORDINATES ON THE 3D MODEL.

% % 1.1 Render.
[refDepth, refRendered, refUnproject, outA, outR, outT] = renderer(width, height, model_name, 0, 0, 0, -90, 0, 0, 'zxy');
%[refDepth, refRendered, refUnproject, outA, outR, outT]=renderer(width, height, model_name);

% Display the results.
% figure, imshow(refRendered);

% View the 3D points of the model.
% figure, plot3(refUnproject(:,:,1),refUnproject(:,:,2),refUnproject(:,:,3),'.');

% % 1.2 Get facial features from the input image.
% Read keypoints from file.
if exist(keypoints_file, 'file') == 2
    delimiterIn = ' ';
    headerlinesIn = 1;
    kps = importdata(keypoints_file, delimiterIn, headerlinesIn);
    pts_2D = uint32(kps.data());
    
    % Show 2D points from input image.
    % disp(pts_2D)
    % hold on;
    % plot(pts_2D(:,1), pts_2D(:,2), '.');
    
    % Fill 3D vector with zeros.
    pts_3D=zeros(size(pts_2D, 1), 3);
    
    % Get 3D coordinates of facial features, using the unproject map from image 2D to model 3D.
    for j=1:size(pts_2D, 1)
        pts_3D(j, :) = refUnproject(pts_2D(j, 2), pts_2D(j, 1), 1:3);
    end   
    
    fileID = fopen(pts3D_file,'w');
    fprintf(fileID,'%6.5f %6.5f %6.5f\n',pts_3D);
end