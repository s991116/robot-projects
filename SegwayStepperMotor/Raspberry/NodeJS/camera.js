module.exports = function() {
    const ffmpegCmd = 'ffmpeg';// -f v4l2 -framerate 25 -video_size 640x480 -i /dev/video0 -f mpegts -codec:v mpeg1video -s 640x480 -b:v 1000k -bf 0 http://localhost:8081/supersecret';
    const ffmpegArg =  ['-f', 'v4l2', '-framerate', '25', '-video_size', '640x480', '-i', '/dev/video0', '-f', 'mpegts', '-codec:v', 'mpeg1video', '-s', '640x480', '-b:v', '1000k', '-bf', '0', 'http://localhost:8081/supersecret'];
    
    const { spawn } = require('child_process');

    var ffmpegProces;
    var playing = false;

    let start = () => {
       ffmpegProces = spawn(ffmpegCmd, ffmpegArg);
       playing = true;
    }
    
    let stop = () => {
        ffmpegProces.kill('SIGHUP');
        playing = false;
    }

    let toggle = () => {
        if(playing) {
            stop();
        }
        else {
            start();
        }
    }

    let state = () => {
        return playing;
    }

    return{
        start: start,
        stop: stop,
        toggle: toggle,
        state: state,
    }
}