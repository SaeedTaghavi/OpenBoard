/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UBUNINOTESWINDOWCONTROLLER_H_
#define UBUNINOTESWINDOWCONTROLLER_H_

#include <QtGui>
#include <QTime>
#include <QTimer>

#include "gui/UBRightPalette.h"

class UBDesktopPalette;
class UBBoardView;
class UBGraphicsScene;
class UBDesktopPenPalette;
class UBDesktopMarkerPalette;
class UBDesktopEraserPalette;
class UBActionPalette;
class UBKeyboardPalette;
class UBMainWindow;

#define PROPERTY_PALETTE_TIMER      1000

/**
 * The uninotes controller. This object allocate a uninotes window and implements all the actions corresponding to
 * the uninotes button:
 * - Go to Uninotes
 * - Custom capture
 * - Window capture
 * - Screen capture
 */
class UBDesktopAnnotationController : public QObject
{
    Q_OBJECT;

    public:
        UBDesktopAnnotationController(QObject *parent = 0);
        virtual ~UBDesktopAnnotationController();
        void showWindow();
        void hideWindow();

        UBDesktopPalette *desktopPalette();
        UBBoardView *drawingView();

    public slots:

        void screenLayoutChanged();
        void goToUniboard();
        void customCapture();
        void windowCapture();
        void screenCapture();
        void updateShowHideState(bool pEnabled);

        void close();

        void stylusToolChanged(int tool);
        void updateBackground();

        void showKeyboard(bool show);
        void showKeyboard(); //X11 virtual keyboard working only needed

    signals:
        /**
         * This signal is emitted once the screenshot has been performed. This signal is also emitted when user
         * click on go to uniboard button. In this case pCapturedPixmap is an empty pixmap.
         * @param pCapturedPixmap QPixmap corresponding to the capture.
         */
        void imageCaptured(const QPixmap& pCapturedPixmap, bool pageMode);
        void restoreUniboard();

    protected:
        QPixmap getScreenPixmap();

        UBBoardView* mTransparentDrawingView;       
        UBGraphicsScene* mTransparentDrawingScene;

    private slots:
        void desktopPenActionToggled(bool checked);
        void desktopMarkerActionToggled(bool checked);
        void desktopEraserActionToggled(bool checked);
        void eraseDesktopAnnotations();
        void penActionPressed();
        void markerActionPressed();
        void eraserActionPressed();
        void penActionReleased();
        void markerActionReleased();
        void eraserActionReleased();
        void onDesktopPaletteMaximized();
        void onDesktopPaletteMinimize();
        void onTransparentWidgetResized();
        void refreshMask();

    private:
        void setAssociatedPalettePosition(UBActionPalette* palette, const QString& actionName);
        void togglePropertyPalette(UBActionPalette* palette);
        void updateMask(bool bTransparent);

        UBDesktopPalette *mDesktopPalette;
        UBKeyboardPalette *mKeyboardPalette;
        UBDesktopPenPalette* mDesktopPenPalette;
        UBDesktopMarkerPalette* mDesktopMarkerPalette;
        UBDesktopEraserPalette* mDesktopEraserPalette;

        UBRightPalette* mRightPalette;

        QTime mPenHoldTimer;
        QTime mMarkerHoldTimer;
        QTime mEraserHoldTimer;
        QTimer mHoldTimerPen;
        QTimer mHoldTimerMarker;
        QTimer mHoldTimerEraser;

        bool mWindowPositionInitialized;
        bool mIsFullyTransparent;
        bool mDesktopToolsPalettePositioned;
        bool mPendingPenButtonPressed;
        bool mPendingMarkerButtonPressed;
        bool mPendingEraserButtonPressed;
        bool mbArrowClicked;

        int mBoardStylusTool;
        int mDesktopStylusTool;

        QPixmap mMask;

};

#endif /* UBUNINOTESWINDOWCONTROLLER_H_ */
