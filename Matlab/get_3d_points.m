width = 640;
height = 480;
model = '3DModels/Faces/Model_2/3DScan.obj'; % 3D model.
keypoints = '../Dataset/Correspondences/000001_pts2d.txt'; % Input 2D points.
pts3D_file = '../Dataset/Correspondences/000001_pts3d.txt'; % Output 3D corresponce points.

% % 1.1 Render the 3D model.
[refDepth, refRendered, refUnproject, outA, outR, outT] = renderer(width, height, model, 0, 0, 0, -90, 0, 0, 'zxy');
%[refDepth, refRendered, refUnproject, outA, outR, outT]=renderer(width, height, model_name);

% Display the results.
figure, imshow(refRendered);

% Display the 3D points of the model.
% figure, plot3(refUnproject(:,:,1),refUnproject(:,:,2),refUnproject(:,:,3),'.');

% % 1.2 Get features from the input image.
% Read keypoints from file.
if exist(keypoints_file, 'file') == 2
    delimiterIn = ' ';
    headerlinesIn = 1;
    kps = importdata(keypoints_file, delimiterIn, headerlinesIn);
    pts_2D = uint32(kps.data());
    
    % Display the 2D points from input image.
    % disp(pts_2D)
    % hold on;
    % plot(pts_2D(:,1), pts_2D(:,2), '.');
    
    % Fill the 3D vector with zeros.
    pts_3D=zeros(size(pts_2D, 1), 3);
    
    % Get 3D coordinates of features, using the unproject map from image 2D to model 3D.
    for j=1:size(pts_2D, 1)
        pts_3D(j, :) = refUnproject(pts_2D(j, 2), pts_2D(j, 1), 1:3);
    end   
    
    % Save the correspondence 3D points in a text file.
    fileID = fopen(pts3D_file,'w');
    fprintf(fileID,'%6.5f %6.5f %6.5f\n',pts_3D);
end