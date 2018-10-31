function varargout = fifa3d(varargin)
% FIFA3D MATLAB code for fifa3d.fig
%      FIFA3D, by itself, creates a new FIFA3D or raises the existing
%      singleton*.
%
%      H = FIFA3D returns the handle to a new FIFA3D or the handle to
%      the existing singleton*.
%
%      FIFA3D('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in FIFA3D.M with the given input arguments.
%
%      FIFA3D('Property','Value',...) creates a new FIFA3D or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before fifa3d_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to fifa3d_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help fifa3d

% Last Modified by GUIDE v2.5 30-Nov-2015 23:15:35

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @fifa3d_OpeningFcn, ...
                   'gui_OutputFcn',  @fifa3d_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before fifa3d is made visible.
function fifa3d_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to fifa3d (see VARARGIN)

% Choose default command line output for fifa3d
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes fifa3d wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = fifa3d_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% Load the Background Image %

backgroundAxis = axes('units','normalized',...
        'position',[0 0 1 1]);

uistack(backgroundAxis,'bottom'); % moves axis to the bottom.

coverImg = imread('images/cover.png'); % gets the cover image.

modifiedImg = imagesc(coverImg);

colormap gray;

set(backgroundAxis,'handlevisibility','off', ...
        'visible','off'); % sets the axis visibility to off.
    
    % Load the Background Image %
    


% --- Executes on button press in btnPlay.
function btnPlay_Callback(hObject, eventdata, handles)
% hObject    handle to btnPlay (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

main;