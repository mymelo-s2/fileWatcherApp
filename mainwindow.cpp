#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tableModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    // --- ダークテーマ＋テーブル枠線を設定 ---
    this->setStyleSheet(R"(
        /* ウィンドウ全体の背景 */
        QMainWindow {
            background-color: black;
        }
        /* QTableView 全体に枠線（外枠）を追加 */
        QTableView {
            background-color: black;
            color: white;
            gridline-color: white;
            border: 1px solid white;         /* ← 外枠 */
            show- grid: true;                /* グリッド線を表示 */
        }
        /* セルの選択時（お好みで） */
        QTableView::item:selected {
            background-color: #333333;
        }
        /* ヘッダー部分 */
        QHeaderView::section {
            background-color: black;
            color: white;
            border: 1px solid white;         /* ヘッダーも枠線 */
        }
    )");

    // カラム数：5 に変更
    tableModel->setColumnCount(5);
    tableModel->setHeaderData(0, Qt::Horizontal, QStringLiteral("No"));
    tableModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("TargetId"));
    tableModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("start"));
    tableModel->setHeaderData(3, Qt::Horizontal, QStringLiteral("end"));
    tableModel->setHeaderData(4, Qt::Horizontal, QStringLiteral("symbolType"));

    // TableView にモデルをセット
    ui->tableView->setModel(tableModel);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    // **縦ヘッダーを非表示**して「1,2,3…」を消す
    ui->tableView->verticalHeader()->setVisible(false);

    // グリッド線が確実に出るように明示的に
    ui->tableView->setShowGrid(true);

    // 場合によってはフレームも設定しておくと確実
    ui->tableView->setFrameShape(QFrame::NoFrame);  // 枠は CSS のペインに任せる
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFileDetected(const QString& filePath)
{
    // QFileInfo でファイル情報を取得
    QFileInfo fi(filePath);

    // 例として：
    //  TargetId   = ベースネーム（拡張子なし）
    //  start      = ファイル作成日時
    //  end        = 最終更新日時
    //  symbolType = 拡張子
    // QString targetId   = fi.completeBaseName();
    // QString startTime  = fi.birthTime().toString(Qt::ISODate);
    // QString endTime    = fi.lastModified().toString(Qt::ISODate);
    // QString symbolType = fi.suffix();
    // 現在の行数(追加前)＋1 を No とする
    int no = tableModel->rowCount() + 1;
    const QString targetId = QString("AA%1").arg(no, 3, 10, QLatin1Char('0'));
    QString startTime  = "2025-07-25T00:00:00Z";
    QString endTime    = "2025-07-25T01:00:00Z";
    QString symbolType = "BUY";


    // 新しい行を作成
    QList<QStandardItem*> items;
    items << new QStandardItem(QString::number(no))
          << new QStandardItem(targetId)
          << new QStandardItem(startTime)
          << new QStandardItem(endTime)
          << new QStandardItem(symbolType);

    // 行末に追加
    tableModel->appendRow(items);
}
