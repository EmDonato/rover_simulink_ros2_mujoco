function [data, info] = float32Array8
%Float32Array8 gives an empty data for interfaces/Float32Array8
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'interfaces/Float32Array8';
[data.data, info.data] = ros.internal.ros2.messages.ros2.default_type('single',8,0);
info.MessageType = 'interfaces/Float32Array8';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'data';
