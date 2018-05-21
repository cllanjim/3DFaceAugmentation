width = 640; % The input image width.
height = 480; % The input image height.
model = '../Dataset/Faces/Models/000001/Model_002/3DScan.obj'; % The 3D model path.
model_kps = '../Dataset/Faces/Models/000001/Model_002/keypoints.txt'; % Features from 2D image from 3D model.
model_3D_pts = '../Dataset/Faces/Models/000001/Model_002/3D_points.txt'; % Output for 3D correspondence points.
camera_params = '../Dataset/Faces/Models/000001/Model_002/camera_params.txt'; % Output for camera parameters.

% Render the 3D model.
[refDepth, refRendered, refUnproject, outA, outR, outT] = renderer(width, height, model, 0, 0, 0, -90, 0, 0, 'xyz');
figure, imshow(refRendered);

% Write camera parameters to text file.
dlmwrite(camera_params, outA, 'delimiter', ' ', 'precision', 10);
dlmwrite(camera_params, outR, '-append', 'delimiter', ' ', 'roffset', 1)
dlmwrite(camera_params, outT, '-append', 'delimiter', ' ', 'roffset', 1)

% Display camera parameters.
disp(outA);
disp(outR);
disp(outT);

% Read model keypoints file.
if exist(model_kps, 'file') == 2
    delimiterIn = ' ';
    headerlinesIn = 1;
    kps = importdata(model_kps, delimiterIn, headerlinesIn);
    pts_2D = uint32(kps.data());
    disp(pts_2D);
    
    % Fill the 3D vector with zeros.
    pts_3D=zeros(size(pts_2D, 1), 3);
    
     % Get 3D coordinates of features, using the unproject map from image 2D to model 3D.
    for j=1:size(pts_2D, 1)
        pts_3D(j, :) = refUnproject(pts_2D(j, 2), pts_2D(j, 1), 1:3);
    end 
    
    % Save the correspondence 3D points in a text file.
    fileID = fopen(model_3D_pts, 'w');
    fprintf(fileID, '%8.8f %8.8f %8.8f\n', pts_3D);
    disp(pts_3D);
end