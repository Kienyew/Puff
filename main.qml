import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.Layouts
import QtMultimedia
import QtQuick.LocalStorage

import kienyew.github

Window {
    // format time in milliseconds to presentable string
    function formatTime(time) {
        let totalSeconds = Math.floor(time / 1000);
        let minutes = Math.floor(totalSeconds / 60);
        let seconds = totalSeconds % 60;

        // left zero padding
        seconds = ("00" + String(seconds)).slice(-2);

        return `${minutes}:${seconds}`;
    }


    property bool simplify_view: false;
    id: root
    title: "Puff"
    color: "#88DDDDDD" // ARGB
    visible: true
    width: 500
    height: 888

    Shortcut {
        sequence: "h"
        onActivated: {
            simplify_view = !simplify_view;
        }
    }

    ColumnLayout {
        width: root.width
        height: root.height
        spacing: 20
        anchors.margins: 20

        // The scrollable lyric view
        LyricsView {
            id: lyricView
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        // Slider and time
        Row {
            Layout.fillWidth: true
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            visible: !simplify_view
            Slider {
                width: parent.width - timeLabel.width
                id: slider
                enabled: player.seekable
                value: player.duration > 0 ? player.position / player.duration : 0;
                onMoved: {
                    player.position = player.duration * slider.position;
                }
                anchors.verticalCenter: parent.verticalCenter
            }

            Text {
                id: timeLabel
                leftPadding: 20
                text: `${formatTime(player.position)} | ${formatTime(player.duration)}`
                horizontalAlignment: Text.AlignHCenter

            }
        }

        // Three buttons
        Row {
            Layout.fillWidth: false
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 20
            spacing: 10
            visible: !simplify_view


            // Select LRC file button
            Button {
                text: "LRC file"
                FileDialog {
                    id: lrcFileDialog
                    title: "Choose a LRC file"
                    fileMode: FileDialog.OpenFile
                    nameFilters: ["LRC files (*.lrc)"]
                    onAccepted: {
                        lyricView.lrcSource = selectedFile
                        config.recentLrcFile = selectedFile
                    }
                }

                onClicked: {
                    lrcFileDialog.open()
                }
            }

            // Play and pause button
            Button {
                text: player.playbackState ===  MediaPlayer.PlayingState ? "Pause" : "Play"
                onClicked: {
                    switch(player.playbackState) {
                    case MediaPlayer.PlayingState: player.pause(); break;
                    case MediaPlayer.PausedState: player.play(); break;
                    case MediaPlayer.StoppedState: player.play(); break;
                    }
                }
            }

            // Select Audio file button
            Button {
                text: "Audio file"
                FileDialog {
                    id: audioFileDialog
                    title: "Choose an audio file"
                    fileMode: FileDialog.OpenFile
                    onAccepted: {
                        player.source = selectedFile
                        config.recentAudioFile = selectedFile;
                    }
                }
                onClicked: {
                    audioFileDialog.open()
                }
            }

        }
    }

    // The media player to play audio
    MediaPlayer {
        id: player
        audioOutput: AudioOutput {}
        loops: MediaPlayer.Infinite
        source: config.recentAudioFile
    }

    // Timer to naively scroll to current lyric line every 100 milliseconds
    Timer {
        interval: 100
        repeat: true
        running: true
        onTriggered: {
            lyricView.scrollToTime(player.position);
        }
    }

    Component.onCompleted: {
        player.play();
    }


}

