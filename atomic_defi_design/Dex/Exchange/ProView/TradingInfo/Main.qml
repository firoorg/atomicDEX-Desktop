import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import Qaterial 1.0 as Qaterial

import Dex.Themes 1.0 as Dex
import Dex.Components 1.0 as Dex
import AtomicDEX.MarketMode 1.0
import "../../../Constants"
import "../../../Components"
import "../../Trade"
import "../../ProView"

ColumnLayout
{
    Layout.preferredWidth: 450
    Layout.fillHeight: true
    property alias currentIndex: tabView.currentIndex

    Qaterial.LatoTabBar
    {
        id: tabView
        property int pair_chart_idx: 0
        property int order_idx: 1
        property int history_idx: 2

        background: null
        Layout.leftMargin: 6

        Qaterial.LatoTabButton
        {
            text: qsTr("Chart")
            font.pixelSize: 14
            textColor: checked ? Dex.CurrentTheme.foregroundColor : Dex.CurrentTheme.foregroundColor2
            textSecondaryColor: Dex.CurrentTheme.foregroundColor2
            indicatorColor: Dex.CurrentTheme.foregroundColor
        }
        Qaterial.LatoTabButton
        {
            text: qsTr("Orders")
            font.pixelSize: 14
            textColor: checked ? Dex.CurrentTheme.foregroundColor : Dex.CurrentTheme.foregroundColor2
            textSecondaryColor: Dex.CurrentTheme.foregroundColor2
            indicatorColor: Dex.CurrentTheme.foregroundColor
        }
        Qaterial.LatoTabButton
        {
            text: qsTr("History")
            font.pixelSize: 14
            textColor: checked ? Dex.CurrentTheme.foregroundColor : Dex.CurrentTheme.foregroundColor2
            textSecondaryColor: Dex.CurrentTheme.foregroundColor2
            indicatorColor: Dex.CurrentTheme.foregroundColor
        }
    }

    Rectangle
    {
        Layout.fillHeight: true
        color: Dex.CurrentTheme.floatingBackgroundColor
        radius: 10
        Layout.preferredWidth: 450

        Qaterial.SwipeView
        {
            id: swipeView
            clip: true
            interactive: false
            currentIndex: tabView.currentIndex
            anchors.fill: parent

            ColumnLayout
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.topMargin: 8
                spacing: 8
                
                // Ticker selectors.
                TickerSelectors
                {
                    id: selectors
                    Layout.preferredWidth: 435
                    Layout.preferredHeight: 85
                    Layout.leftMargin: 8
                    Layout.rightMargin: 8
                }

                // Chart
                Chart
                {
                    id: chart
                    Layout.topMargin: 8
                    Layout.leftMargin: 5
                    Layout.rightMargin: 5
                    Layout.fillHeight: true
                    width: 435
                    height: 240
                }

                PriceLineSimplified
                {
                    id: price_line
                    Layout.bottomMargin: 12
                    Layout.leftMargin: 5
                    Layout.rightMargin: 5
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    width: 435
                }
            }

            onCurrentIndexChanged:
            {
                swipeView.currentItem.update();
            }

            OrdersPage { clip: true }

            OrdersPage
            {
                is_history: true
                clip: true
            }
        }
    }
}
