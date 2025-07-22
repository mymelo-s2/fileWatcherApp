#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onFileDetected(const QString& filePath);

private:
    Ui::MainWindow *ui;

    // テーブル用のモデル
    QStandardItemModel *tableModel;
};
