#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QGroupBox *G_buttons, *G_inputs, *G_outputs;
    QPushButton *B_qWLS, *B_qWUS, *B_qWD, *B_rezult, *B_compare;
    QScrollArea *S_outputs;
    QLabel *L_name, *L_n, *L_lambda, *L_mu, *L_m;
    QTextEdit *T_help, *T_n, *T_lambda, *T_mu, *T_m, *T_name;
    QVector <QPushButton *> B_outputs;
    QVector <QTextEdit *> T_outputs;
    QVector <int> mode_outputs, n_outputs, m_outputs;
    QVector <float> lambda_outputs, mu_outputs;
    QVector <QString>  name_outputs;
    QMenu  *mfile;
    QAction *anew, *aopen, *asave, *aexit;
    int this_output = 0;
    short int mode;
    void createWidgets();
    void createConnections();
    float factorial(float n);
    float f_pf(float val, int i, int j = 0);
    void count();
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void slotButton();
    void slotShowHide();
    void slotAction();
};

class CompareDialog : public QDialog
{
    Q_OBJECT
public:
    QPushButton *B_add, *B_export;
    QComboBox *combo;
    QScrollArea *S_mode1, *S_mode2, *S_mode3;
    QTableWidget *Tab_mode1, *Tab_mode2, *Tab_mode3;
    QTabWidget *tabs;
    QVector <bool> SMO_in_tables;
    int k1 = 0, k2 = 0, k3 = 0;
    void createConnections();
    CompareDialog( QWidget* parent = 0 );
    ~CompareDialog();
public slots:
    void slotButton();
};

#endif // MAINWINDOW_H
