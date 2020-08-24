#pragma once
#pragma execution_character_set("utf-8")

#include <CubismFramework.hpp>

#include <QOpenGLWidget>

#include <string>
#include <queue>


class QMouseEvent;
class QTimer;
class QHotkey;
class QMenu;
class QAction;

class Allocator;
class ScreenGrabber;
class SettingsMenu;
class MouseTracker;
class ItemManager;
class Model;
class ThLauncher;



//�ƹ�Live2Dģ�͡����ڡ�����ģ��ĸ���
class Live2DWidget : public QOpenGLWidget
{
    Q_OBJECT

public:

    //ͨ��ģ�����Ƴ�ʼ��
    Live2DWidget(std::string modelName);

    //����
    ~Live2DWidget();



    //����ģ��
    void paintGL() override;



    //����ƶ��¼��������׷������������qt��mouseMoveEvent��ͬ
    void MouseMoveEvent(int x, int y);

    //��갴���¼�
    void mousePressEvent(QMouseEvent* e) override;

    //����ͷ��¼�
    void mouseReleaseEvent(QMouseEvent* e) override;

    //���˫���¼�
    void mouseDoubleClickEvent(QMouseEvent* e) override;

    //��д�ı����¼���������ֹ�����ʹ���ڻ�ý���
    bool nativeEvent(const QByteArray& b, void* m, long* r) override;

    //�Ҽ��˵��¼�
    void contextMenuEvent(QContextMenuEvent* e) override;

signals:

    //��ͼ�ź�
    void TakeScreenshotSignal(bool fastMode);

    //�༭���н�ͼ�ź�
    void EditScreenshotSignal();

    //������Ʒ��ҷ�ź�
    void EndDragItemSignal();

    //�����Ʒ�ź�
    void AddItemSignal(int type);

    //��ҷ��Ʒ�ź�
    void DragItemSignal();

    //�˳��ź�
    void CloseSignal(int exitCode = 0);

private:

    //��ʱ����ʱ��
    QTimer* _timer = nullptr;
    int _frameTime = 0;
    int _time = 0;

    

    //��Ļ��С
    int _screenWidth = 0;
    int _screenHeight = 0;



    //cubism��ʼ�����
    Allocator* _cubismAllocator = nullptr;
    Csm::CubismFramework::Option* _cubismOption = nullptr;

    //����������
    ThLauncher* _thLauncher = nullptr;

    //��Ļ��ͼ��
    ScreenGrabber* _screenGrabber   = nullptr;
    
    //��Ʒ������
    ItemManager* _itemManager = nullptr;

    //������봦��
    MouseTracker* _mouseTracker     = nullptr;

    double _mouseX = 0;
    double _mouseY = 0;
    bool _lBtnPressed = false;
    bool _rBtnPressed = false;
    bool _lBtnDoubleClicked = false;



    //�������ݣ�����ÿ֡����һ��
    void _Update();



    //ģ�� 
    Model* _model = nullptr;

    double _modelSize = 0.0;
    double _modelX = 0.0;
    double _modelY = 0.0;
    double _modelXLastFrame = 0.0;
    double _modelYLastFrame = 0.0;
    double _modelXMax = 0.0;
    double _modelXMin = 0.0;
    double _modelYMax = 0.0;
    double _modelYMin = 0.0;
    double _modelVelocityX = 0.0;
    double _modelVelocityY = 0.0;

    //ͨ��ģ��·��������ģ��
    void _LoadModel(std::string fileName);
    
    //��ʼ��ģ�͵Ĵ�С�����ں���Ļ��Ե����ײ��⣩
    void _SetupModelSize();

    //�ͷ�ģ��
    void _ReleaseModel();

    //��ģ���ƶ�һ������
    void _MoveModelBy(double dx, double dy);

    //��ģ���ƶ���ָ����
    void _MoveModelTo(double x, double y);

    //����ģ������Ļ��
    void _KeepModelInScreen();

    //��ģ��ĳ����ײ����ļ��
    bool _ModelHitTest(int x, int y, std::string hitArea = "Body") const;

    

    //���ò˵�
    SettingsMenu* _settingsMenu = nullptr;

    //����������Ϣ
    void _UpdateSettings();



    //�ȼ�
    std::vector<QHotkey*> _hotkeys;
    
    //��ʼ���ȼ�
    void _SetupHotkeys();

    //�����ȼ�������ر�
    void _SetHotkeysState(bool enable);



    //�ƻ������ı���
    using PlanFunction = void (Live2DWidget::*)();

    //�ӳ�һ��ʱ����еļƻ�����
    struct Plan
    {
        PlanFunction function;
        int executeTime;
        //�Ƚϴ�С��ʽ�෴������ʱ��ִ��ʱ���С��������
        bool operator<(const Plan& other)const
        {
            return executeTime > other.executeTime;
        }
    };

    std::priority_queue<Plan> _plans;

    //��Ӽƻ�
    void _AddPlan(PlanFunction func, int delay);

    //���¼ƻ��б�
    void _UpdatePlan();



    //���ֶ��������ǵ�״̬
    bool _isDragging        = false;
    bool _isDraggingItem    = false;
    bool _isFloating        = true;
    bool _isSleeping        = false;
    bool _isSmiling         = false;
    bool _isEyeSquinting    = false;
    bool _isEyeBlinking     = false;
    bool _isHotkeyDisabled  = false;
    bool _isHidingByHotkey  = false;
    bool _isLookingAtOuter  = false;
    bool _isCameraFlashing  = false;

    int _item = 0;
    double _itemX = 0.0;
    double _itemY = 0.0;
    double _itemSize = 0.0;

    double _dragStartMouseX = 0.0;
    double _dragStartMouseY = 0.0;
    double _dragStartModelX = 0.0;
    double _dragStartModelY = 0.0;

    double _lookAtX         = 0.0;
    double _lookAtY         = 0.0;
    double _headLeanAngle   = 0.0;
    double _mouthState      = 0.0;
    double _eyeState        = 0.0;

    double _lastFrameMouseX = 0.0;  
    double _lastFrameMouseY = 0.0;
    int _lastTriggeredSleepTime         = 0;
    int _lastTriggeredSmileTime         = 0;
    int _lastTriggeredEyeBlinkTime      = 0;
    int _lastTriggeredLookAtOuterTime   = 0;

    int _eyeBlinkStartTime      = 0;
    int _cameraFlashStartTime   = 0;
    int _mouseStillStartTime    = 0;  

    //��ʼ�϶�
    void _StartDrag();

    //�����϶�
    void _EndDrag();

    //��ʼ�϶���Ʒ
    void _StartDragItem();

    //�����϶���Ʒ
    void _EndDragItem();

    //������Ʒ
    void _ChangeItem(int item, bool dropItem);

    //��ȡһ�������Ʒ�������ȡ�����ǰ���е���Ʒ)
    int _GetRandomItem() const;

    //����
    void _Wake();

    //����
    void _Sleep();

    //����
    void _Sit();

    //Ư��
    void _Float();

    //��ʼ�����ۻ����۵�΢Ц
    void _StartSmile(bool withEyeSquinted);

    //����΢Ц
    void _EndSmile();

    //գ��
    void _StartEyeBlink();

    //����գ��
    void _EndEyeBlink();

    //������Ļ��
    void _StartLookAtOuter();

    //����׷�����
    void _EndLookAtOuter();

    //�����˸
    void _StartCameraFlash();

    //���������˸
    void _EndCameraFlash();

    //���û򲻽����ȼ������ػ���
    void _Hide(bool withHotkeyDisabled);

    //��ʾ���棬��֤�ȼ���
    void _Show();


    //��Ļ��ͼ��ɻص�
    void _OnScreenshotGrabbed();

    //��Ļ��ͼ��ʼ�༭�ص�
    void _OnScreenshotEditStarted();

    //��Ļ��ͼ�����༭�ص�
    void _OnScreenshotEditEnded(bool accept);

    //�����������ص�
    void _OnThLauncherLaunched();


    //�˵������¼�
    QMenu* _menu = nullptr;
    QAction* _actionClose                   = nullptr;
    QAction* _actionSitOrFloat              = nullptr;
    QAction* _actionSleepOrWake             = nullptr;
    QAction* _actionTakeScreenshot          = nullptr;
    QAction* _actionTakeFastScreenshot      = nullptr;
    QAction* _actionEditScreenshot          = nullptr;
    QAction* _actionOpenScreenshotFolder    = nullptr;
    QAction* _actionOpenSettingsMenu        = nullptr;
    QAction* _actionChangeItem              = nullptr;
    QAction* _actionClearItem               = nullptr;
    QAction* _actionOpenAboutsDialog        = nullptr;
    QAction* _actionHideOrShow              = nullptr;
    QAction* _actionOpenThLauncher          = nullptr;

    //�˵�:�رն���
    void _OnActionClose();

    //�˵�:��ͼ����
    void _OnActionTakeScreenshot();

    //�˵�:���ٽ�ͼ����
    void _OnActionTakeFastScreenshot();

    //�˵�:�򿪽�ͼ�ļ��ж���
    void _OnActionOpenScreenshotFolder();

    //�˵�:�༭��ͼ����
    void _OnActionEditScreenshot();

    //�˵�:���»�������
    void _OnActionSitOrFloat();

    //�˵�:���߻��Ѷ���
    void _OnActionSleepOrWake();

    //�˵�:�����ò˵�����
    void _OnActionOpenSettingsMenu();

    //�˵�:��ʾ�����ض���
    void _OnActionHideOrShow();

    //�˵�:�򿪹��ڽ��涯��
    void _OnActionOpenAboutsDialog();

    //�˵�:�л���Ʒ����
    void _OnActionChangeItem();

    //�˵�:�򿪶���������
    void _OnActionOpenThLauncher();
};
