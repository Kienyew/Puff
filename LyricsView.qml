import QtQuick
import QtQml
import QtMultimedia

import kienyew.github

ListView {
    property alias lrcSource: model.lyricSource;
    property int lineHeight: 70
    id: root
    clip: true
    model: model
    snapMode: ListView.SnapToItem
    highlightRangeMode: ListView.ApplyRange
    preferredHighlightBegin: height / 2 - lineHeight / 2
    preferredHighlightEnd: height / 2 + lineHeight / 2
    highlightFollowsCurrentItem: true
    highlightMoveDuration: 500
    interactive: true
    reuseItems: true

    LyricsModel {
        id: model
        lyricSource: "file:///home/kienyew/Audios/Playlist/僕らのてえには何もないけど.lrc"
    }

    delegate: Rectangle {
        id: lyricLine
        required property int index
        required property int timestamp
        required property string sentence

        color: "transparent"
        width: root.width
        height: lineHeight
        Text {
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: (index === root.currentIndex) ? 22 : 18
            text: sentence
            color: "#121212"
            opacity: (index === root.currentIndex) ? 1.0 : 0.8
            wrapMode: Text.WordWrap

            Behavior on font.pixelSize {
                NumberAnimation {
                    duration: 50
                }
            }
        }
    }

    // scoll to the appropriate lyric line at `time` in milliseconds
    function scrollToTime(time) {
        for (let i = 1 ; i < root.count; ++i) {
            let line =  model.getLyricLine(i);
            if (line !== null && line.timestamp > time) {
                if (root.currentIndex != i - 1) {
                    root.currentIndex = i - 1;
                }
                return;
            }
        }

        if (root.currentIndex != root.count - 1) {
            root.currentIndex = root.count - 1;
        }
    }


}
