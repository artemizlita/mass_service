#include "mainwindow.h"
#include <Qt>

int k = 0;
QVector <QString> SMO_names;
QVector <int> SMO_mode, SMO_n, SMO_m;
QVector <float> SMO_lambda, SMO_mu, SMO_p1, SMO_p2, SMO_p3, SMO_p4, SMO_p5;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Анализ СМО");
    setWindowIcon(QIcon("C:/Users/Andrey/Documents/Qt Creator projects/ISMO_final/icons/SMO.png"));
    createWidgets();
    createConnections();
}

void MainWindow::createWidgets () {
    setFixedSize(700, 420);
    G_buttons = new QGroupBox(this);
    G_buttons->setGeometry(10, 30, 220, 160);

    B_qWLS = new QPushButton("Многоканальная СМО\n с ограниченной очередью", G_buttons);
    B_qWLS->setGeometry(10, 10, 200, 40);
    B_qWLS->setStyleSheet("font-size: 14px");
    B_qWUS = new QPushButton("Многоканальная СМО\n с неограниченной очередью", G_buttons);
    B_qWUS->setGeometry(10, 60, 200, 40);
    B_qWUS->setStyleSheet("font-size: 14px");
    B_qWD = new QPushButton("Многоканальная СМО\n с отказами", G_buttons);
    B_qWD->setGeometry(10, 110, 200, 40);
    B_qWD->setStyleSheet("font-size: 14px");

    G_inputs = new QGroupBox(this);
    G_inputs->setGeometry(10, 200, 220, 210);

    L_name = new QLabel(G_inputs);
    L_name->setGeometry(10, 10, 100, 30);
    L_name->setStyleSheet("font-size: 12px");
    L_name->setText("Название СМО ");
    L_name->setVisible(0);
    L_n = new QLabel(G_inputs);
    L_n->setGeometry(10, 50, 100, 30);
    L_n->setStyleSheet("font-size: 12px");
    L_n->setText("Количество\nканалов СМО");
    L_n->setVisible(0);
    L_lambda = new QLabel(G_inputs);
    L_lambda->setGeometry(10, 90, 100, 30);
    L_lambda->setStyleSheet("font-size: 12px");
    L_lambda->setText("Интесивность\nзаявок ");
    L_lambda->setVisible(0);
    L_mu = new QLabel(G_inputs);
    L_mu->setGeometry(10, 130, 100, 30);
    L_mu->setStyleSheet("font-size: 12px");
    L_mu->setText("Интенсивность\nобслуживания ");
    L_mu->setVisible(0);
    L_m = new QLabel(G_inputs);
    L_m->setGeometry(10, 170, 100, 30);
    L_m->setStyleSheet("font-size: 12px");
    L_m->setText("Размер\nочереди");
    L_m->setVisible(0);

    T_name = new QTextEdit(G_inputs);
    T_name->setGeometry(100, 10, 110, 30);
    T_name->setStyleSheet("font-size: 16px");
    T_name->setVisible(0);
    T_n = new QTextEdit(G_inputs);
    T_n->setGeometry(100, 50, 110, 30);
    T_n->setStyleSheet("font-size: 16px");
    T_n->setVisible(0);
    T_lambda = new QTextEdit(G_inputs);
    T_lambda->setGeometry(100, 90, 110, 30);
    T_lambda->setStyleSheet("font-size: 16px");
    T_lambda->setVisible(0);
    T_mu = new QTextEdit(G_inputs);
    T_mu->setGeometry(100, 130, 110, 30);
    T_mu->setStyleSheet("font-size: 16px");
    T_mu->setVisible(0);
    T_m = new QTextEdit(G_inputs);
    T_m->setGeometry(100, 170, 110, 30);
    T_m->setStyleSheet("font-size: 16px");
    T_m->setVisible(0);

    S_outputs = new QScrollArea(this);
    S_outputs->setGeometry(240, 30, 200, 300);

    G_outputs = new QGroupBox(this);
    G_outputs->setGeometry(0, 0, 170, 0);

    B_outputs.resize(100);
    T_outputs.resize(100);
    SMO_names.resize(100);
    SMO_mode.resize(100);
    SMO_n.resize(100);
    SMO_lambda.resize(100);
    SMO_mu.resize(100);
    SMO_m.resize(100);
    SMO_p1.resize(100);
    SMO_p2.resize(100);
    SMO_p3.resize(100);
    SMO_p4.resize(100);
    SMO_p5.resize(100);
    name_outputs.resize(1);
    mode_outputs.resize(1);
    n_outputs.resize(1);
    lambda_outputs.resize(1);
    mu_outputs.resize(1);
    m_outputs.resize(1);
    for (int i = 0; i < 100; ++i) {
        QPushButton *B_output;
        QTextEdit *T_output;
        B_output = new QPushButton(" ", G_outputs);
        B_output->setStyleSheet("font-size: 18px");
        T_output = new QTextEdit(G_outputs);
        T_output->setStyleSheet("font-size: 11px");
        B_outputs[i] = B_output;
        T_outputs[i] = T_output;
        B_outputs[i]->setVisible(0);
        T_outputs[i]->setVisible(0);
        T_outputs[i]->setReadOnly(1);
    }
    B_outputs[0]->setGeometry(0, 0, 170, 30);
    T_outputs[0]->setGeometry(0, 30, 170, 170);

    S_outputs->setWidget(G_outputs);

    T_help = new QTextEdit(this);
    T_help->setGeometry(450, 30, 240, 380);
    T_help->setReadOnly(1);

    QString fName = "C:/Users/Andrey/Documents/Qt Creator projects/ISMO_rus/help_new.txt";
    QFile file(fName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"File not open";
    }
    QString str = file.readAll();
    T_help->setText(str);
    file.close();

    B_rezult = new QPushButton("Рассчитать параметры СМО", this);
    B_rezult->setGeometry(240, 340, 200, 30);
    B_rezult->setStyleSheet("font-size: 14px");
    B_rezult->setEnabled(0);

    B_compare = new QPushButton("Сравнить параметры СМО", this);
    B_compare->setGeometry(240, 380, 200, 30);
    B_compare->setStyleSheet("font-size: 14px");
    B_compare->setEnabled(0);

    menuBar()->setFont(QFont("TimesNewRoman", 10, 1, true));
    mfile = new QMenu("&Файл", this);
    menuBar()->addMenu(mfile);

    anew = new QAction("&Новый", 0);
    aopen = new QAction("&Открыть", 0);
    asave = new QAction("&Сохранить", 0);
    aexit = new QAction("&Выход", 0);
    mfile->addAction(anew);
    mfile->addAction(aopen);
    mfile->addAction(asave);
    mfile->addAction(aexit);
}

void MainWindow::createConnections () {
    connect(B_qWLS, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(B_qWUS, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(B_qWD, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(B_rezult, SIGNAL(clicked()), this, SLOT(slotButton()));
    for (int i = 0; i < 100; ++i) {
        connect(B_outputs[i], SIGNAL(clicked()), this, SLOT(slotShowHide()));
    }
    connect(B_compare, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(anew, SIGNAL(triggered()), this, SLOT(slotAction()));
    connect(aopen, SIGNAL(triggered()), this, SLOT(slotAction()));
    connect(asave, SIGNAL(triggered()), this, SLOT(slotAction()));
    connect(aexit, SIGNAL(triggered()), this, SLOT(slotAction()));
}

void MainWindow::slotButton() {
    if (sender() == B_rezult && k < 100) {

        count();

    } else if (sender() == B_compare) {

        CompareDialog d;
        d.setWindowTitle("Модуль сравнения");
        d.exec();

    } else {
        L_name->setVisible(1);
        L_n->setVisible(1);
        L_lambda->setVisible(1);
        L_mu->setVisible(1);
        T_name->setVisible(1);
        T_n->setVisible(1);
        T_lambda->setVisible(1);
        T_mu->setVisible(1);
        if (sender() == B_qWLS) {
            mode = 0;
            L_m->setVisible(1);
            T_m->setVisible(1);
            T_n->clear();
            T_lambda->clear();
            T_mu->clear();
            T_m->clear();
        }
        if (sender() == B_qWUS) {
            mode = 1;
            L_m->setVisible(0);
            T_m->setVisible(0);
            T_n->clear();
            T_lambda->clear();
            T_mu->clear();
            T_m->clear();
        }
        if (sender() == B_qWD) {
            mode = 2;
            L_m->setVisible(0);
            T_m->setVisible(0);
            T_n->clear();
            T_lambda->clear();
            T_mu->clear();
            T_m->clear();
        }
        B_rezult->setEnabled(1);
    }
}

void MainWindow::slotShowHide() {
    for (int i = 0; i < 100; ++i) {
        if (sender() == B_outputs[i]) {
            if (QApplication::keyboardModifiers() == Qt::ControlModifier) {
                SMO_names.remove(i);
                SMO_mode.remove(i);
                SMO_n.remove(i);
                SMO_lambda.remove(i);
                SMO_mu.remove(i);
                SMO_m.remove(i);
                SMO_p1.remove(i);
                SMO_p2.remove(i);
                SMO_p3.remove(i);
                SMO_p4.remove(i);
                SMO_p5.remove(i);
                name_outputs.remove(i);
                n_outputs.remove(i);
                lambda_outputs.remove(i);
                mu_outputs.remove(i);
                m_outputs.remove(i);
                mode_outputs.remove(i);
                B_outputs[k - 1]->setVisible(0);
                T_outputs[k - 1]->setVisible(0);
                --k;
                if (this_output > i) {
                    --this_output;
                } else if (this_output == i) {
                    T_outputs[i]->setGeometry(0, T_outputs[i]->y(), 170, 171 - T_outputs[i]->height());
                    B_rezult->setText("Рассчитать параметры СМО");
                    T_name->clear();
                    T_n->clear();
                    T_lambda->clear();
                    T_mu->clear();
                    T_m->clear();
                    this_output = k;
                }
                if (k > 0) {
                    G_outputs->setGeometry(0, 0, 170, T_outputs[k - 1]->y() + 1);
                } else {
                    G_outputs->setGeometry(0, 0, 170, 0);
                }
                for (int j = i; j < k; ++j) {
                    B_outputs[j]->setText(B_outputs[j + 1]->text());
                    T_outputs[j]->setText(T_outputs[j + 1]->toPlainText());
                }
            } else {
                if (this_output >= k) {
                    G_outputs->setGeometry(0, 0, 170, G_outputs->height() + 170);
                    B_rezult->setText("Пересчитать параметры СМО");
                    L_name->setVisible(1);
                    L_n->setVisible(1);
                    L_lambda->setVisible(1);
                    L_mu->setVisible(1);
                    T_name->setVisible(1);
                    T_n->setVisible(1);
                    T_lambda->setVisible(1);
                    T_mu->setVisible(1);
                    if (mode_outputs[i] == 0) {
                        L_m->setVisible(1);
                        T_m->setVisible(1);
                    }
                    B_rezult->setEnabled(1);
                }
                if (this_output == i) {
                    T_outputs[this_output]->setGeometry(0, T_outputs[this_output]->y(), 170, 171 - T_outputs[this_output]->height());
                    for (int j = this_output + 1; j < k; ++j) {
                        B_outputs[j]->setGeometry(0, B_outputs[j]->y() - 169, 170, B_outputs[j]->height());
                        T_outputs[j]->setGeometry(0, T_outputs[j]->y() - 169, 170, T_outputs[j]->height());
                    }
                    this_output = k;
                    G_outputs->setGeometry(0, 0, 170, G_outputs->height() - 169);
                    B_rezult->setText("Рассчитать параметры СМО");
                    T_name->clear();
                    T_n->clear();
                    T_lambda->clear();
                    T_mu->clear();
                    T_m->clear();
                } else {
                    if (i > this_output) {
                        T_outputs[this_output]->setGeometry(0, T_outputs[this_output]->y(), 170, 171 - T_outputs[this_output]->height());
                        for (int j = this_output + 1; j < i + 1; ++j) {
                            B_outputs[j]->setGeometry(0, B_outputs[j]->y() - 169, 170, B_outputs[j]->height());
                            T_outputs[j]->setGeometry(0, T_outputs[j]->y() - 169, 170, T_outputs[j]->height());
                        }
                        T_outputs[i]->setGeometry(0, T_outputs[i]->y(), 170, 171 - T_outputs[i]->height());
                    } else {
                        T_outputs[i]->setGeometry(0, T_outputs[i]->y(), 170, 171 - T_outputs[i]->height());
                        for (int j = i + 1; j < this_output + 1; ++j) {
                            B_outputs[j]->setGeometry(0, B_outputs[j]->y() + 169, 170, B_outputs[j]->height());
                            T_outputs[j]->setGeometry(0, T_outputs[j]->y() + 169, 170, T_outputs[j]->height());
                        }
                        T_outputs[this_output]->setGeometry(0, T_outputs[this_output]->y(), 170, 171 - T_outputs[this_output]->height());
                    }
                    this_output = i;
                    mode = mode_outputs[this_output];
                    T_name->setText(name_outputs[this_output]);
                    T_n->setText(QString().number(n_outputs[this_output]));
                    T_lambda->setText(QString().setNum(lambda_outputs[this_output], 'g', 3));
                    T_mu->setText(QString().setNum(mu_outputs[this_output], 'g', 3));
                    if (mode == 0) {
                        L_m->setVisible(1);
                        T_m->setVisible(1);
                        T_m->setText(QString().number(m_outputs[this_output]));
                    } else {
                        L_m->setVisible(0);
                        T_m->setVisible(0);
                    }
                }
            }
        }
    }
}

void MainWindow::slotAction() {
    if (sender() == anew) {
        for (int i = 0; i < k; ++i) {
            B_outputs[i]->setVisible(0);
            T_outputs[i]->setVisible(0);
        }
        G_outputs->setGeometry(0, 0, 170, 0);
        this_output = 0;
        k = 0;
        B_rezult->setEnabled(0);
        L_name->setVisible(0);
        L_n->setVisible(0);
        L_lambda->setVisible(0);
        L_mu->setVisible(0);
        L_m->setVisible(0);
        T_name->setVisible(0);
        T_n->setVisible(0);
        T_lambda->setVisible(0);
        T_mu->setVisible(0);
        T_m->setVisible(0);
    }
    if (sender() == aopen) {
        QString fName = QFileDialog::getOpenFileName(this, tr("Open File"), "./", tr("matr(*.txt)"));
        if (fName != "") {
            QString suf = QFileInfo(fName).suffix();
            if (suf.isEmpty()) fName.append(".txt");
            QFile file(fName);
            if (!file.open(QIODevice::ReadOnly)) {
                qDebug()<<"File not open";
            } else {
                for (int i = 0; i < k; ++i) {
                    B_outputs[i]->setVisible(0);
                    T_outputs[i]->setVisible(0);
                }
                G_outputs->setGeometry(0, 0, 170, 0);
                this_output = 0;
                k = 0;
                QString str;
                QStringList list;
                while (!file.atEnd()) {
                    str = file.readLine();
                    list = str.split(" ");
                    T_name->setText(list[0]);
                    mode = list[1].toInt();
                    T_n->setText(list[2]);
                    T_lambda->setText(list[3]);
                    T_mu->setText(list[4]);
                    if (mode == 0) {
                        T_m->setText(list[5]);
                    }
                    count();
                }
                file.close ();
            }
        }
        B_rezult->setEnabled(0);
        L_name->setVisible(0);
        L_n->setVisible(0);
        L_lambda->setVisible(0);
        L_mu->setVisible(0);
        L_m->setVisible(0);
        T_name->setVisible(0);
        T_n->setVisible(0);
        T_lambda->setVisible(0);
        T_mu->setVisible(0);
        T_m->setVisible(0);
    }
    if (sender() == asave) {
        QString fName = QFileDialog::getSaveFileName(this, tr("Save File"), "./", tr("matr(*.txt)"));
        QString suf = QFileInfo(fName).suffix();
        if (suf.isEmpty()) fName.append(".txt");
        QFile file(fName);
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug()<<"File not open";
        } else {
            QTextStream out(&file);
            out.setRealNumberPrecision(3);
            for (int i = 0; i < k; ++i) {
                out<<name_outputs[i]<<" "<<mode_outputs[i]<<" "<<n_outputs[i]<<" "<<lambda_outputs[i]<<" "<<mu_outputs[i];
                if (mode_outputs[i] == 0) {
                    out<<" "<<m_outputs[i];
                }
                if (i < k - 1) {
                    out<<endl;
                }
            }
            file.close ();
        }
    }
    if (sender() == aexit) {
        qApp->quit();
    }
}

float MainWindow::factorial(float n) {
    if (n < 0) {
        return 0;
    }
    return n ? n * factorial(n - 1) : 1;
}

float MainWindow::f_pf(float val, int i, int j) {
    if(j == 0) j = i;
    return (float)(pow(val, i)/factorial(j));
}

void MainWindow::count() {

    bool ok1, ok2, ok3, ok4 = 1;
    int n = T_n->toPlainText().toInt(&ok1);
    float lambda = T_lambda->toPlainText().toFloat(&ok2);
    float mu = T_mu->toPlainText().toFloat(&ok3);
    int m;
    if (mode == 0) {
        m = T_m->toPlainText().toFloat(&ok4);
    }

    if (ok1 && ok2 && ok3 && ok4) {

        if (this_output >= k) {
            B_outputs[this_output]->setGeometry(0, k * 31, 170, 30);
            T_outputs[this_output]->setGeometry(0, k * 31 + 30, 170, 1);
            G_outputs->setGeometry(0, 0, 170, T_outputs[k]->y() + 1);
        }

        if (mode == 0) {

            float ro = lambda/mu;
            float p_otk;
            float p_obs;
            float l_och;
            float t_smo;

            if (ro == n) {

                float p0 = 1;
                for(int i = 1; i < (n + 2); i++) {
                    float res = f_pf(n, i);

                    if (i == n + 1) {
                        res = f_pf(n, i - 1) * m;
                    }
                    p0 += res;
                    qDebug()<<res;
                }
                p0 = pow(p0, -1);
                qDebug()<<p0;

                p_otk = (f_pf(ro, (n+m), n))*p0*(1/pow(n, m));
                p_obs = (1-p_otk);
                l_och = f_pf(n, n) * m * (m + 1) / 2 * p0;
                t_smo = (l_och/lambda + p_obs/mu);

            } else {

            	float p0 = 1;
            	for(int i = 1; i < (n + m + 1); i++) {
                    float res = f_pf(ro, i);

                    if (i > n) {
                    res += f_pf(ro, i, n) / pow(n, i - n);
                    }
                    p0 += res;
            	}
            	p0 = pow(p0, -1);

            	float p_otk = (f_pf(ro, (n+m), n))*p0*(1/pow(n, m));
            	float p_obs = (1-p_otk);
            	float l_och = (f_pf(ro, n+1, n))*(1-pow(ro/n, m))*(1+m*(1-ro/n))/(1-ro/n)/(1-ro/n)/n*p0;
            	float t_smo = (l_och/lambda + p_obs/mu);

            }

            B_outputs[this_output]->setVisible(1);
            T_outputs[this_output]->setVisible(1);
            B_outputs[this_output]->setText("СМО '" + T_name->toPlainText() + "'");
            T_outputs[this_output]->setText("Входные параметры СМО:\nn = " + QString().number(n) + "\n" +
                                            "lambda = " + QString().setNum(lambda, 'g', 3) + "\n" +
                                            "mu = " + QString().setNum(mu, 'g', 3) + "\n" +
                                            "m = " + QString().number(m) + "\n" +
                                            "Расчитываемые параметры\nСМО:\n" +
                                            "p[otk] = " + QString().setNum(p_otk, 'g', 3) + "\n" +
                                            "p[obs] = " + QString().setNum(p_obs, 'g', 3) + "\n" +
                                            "l[och] = " + QString().setNum(l_och, 'g', 3) + "\n" +
                                            "t[smo] = " + QString().setNum(t_smo, 'g', 3));
            SMO_m[this_output] = m;
            SMO_p1[this_output] = p_otk;
            SMO_p2[this_output] = p_obs;
            SMO_p3[this_output] = l_och;
            SMO_p4[this_output] = t_smo;

        } else if (mode == 1) {

            float ro = lambda/mu;

            float p0 = 1;
            for(int i = 1; i < (n + 1); i++) {
                if(i == n) {
                    int i_var = (i-1);
                    p0 += f_pf(ro, i, i_var)/(n-ro);
                } else {
                    p0 += f_pf(ro, i);
                }
            }
            p0 = pow(p0, -1);

            float n3 = ro;
            float k3 = (n3/n);
            float A = lambda;

            float p_och = f_pf(ro, n, n)*(n/(n-ro))*p0;
            float l_och = ro*(1/(n-ro))*p_och;
            float l_smo = l_och + ro;
            float t_smo = l_och/lambda + ro/mu;

            B_outputs[this_output]->setVisible(1);
            T_outputs[this_output]->setVisible(1);
            B_outputs[this_output]->setText("СМО '" + T_name->toPlainText() + "'");
            T_outputs[this_output]->setText("Входные параметры СМО:\nn = " + QString().number(n) + "\n" +
                                            "lambda = " + QString().setNum(lambda, 'g', 3) + "\n" +
                                            "mu = " + QString().setNum(mu, 'g', 3) + "\n" +
                                            "Расчитываемые параметры\nСМО:\n" +
                                            "p[och] = " + QString().setNum(p_och, 'g', 3) + "\n" +
                                            "l[och] = " + QString().setNum(l_och, 'g', 3) + "\n" +
                                            "l[smo] = " + QString().setNum(l_smo, 'g', 3) + "\n" +
                                            "t[smo] = " + QString().setNum(t_smo, 'g', 3));
            SMO_p1[this_output] = p_och;
            SMO_p2[this_output] = l_och;
            SMO_p3[this_output] = l_smo;
            SMO_p4[this_output] = t_smo;

        } else if (mode == 2) {

            float ro = lambda/mu;
            float p0 = 1;
            for(int i = 1; i < (n + 1); i++) {
                p0 += f_pf(ro, i);
            }
            p0 = pow(p0, -1);
            float p_otk =  (p0*f_pf(ro, n));
            float p_obs = (1-p_otk);
            float A = (p_obs*lambda);
            float n3 = (A/mu);
            float k3 = (n3/n);

            B_outputs[this_output]->setVisible(1);
            T_outputs[this_output]->setVisible(1);
            B_outputs[this_output]->setText("СМО '" + T_name->toPlainText() + "'");
            T_outputs[this_output]->setText("Входные параметры СМО:\nn = " + QString().number(n) + "\n" +
                                            "lambda = " + QString().setNum(lambda, 'g', 3) + "\n" +
                                            "mu = " + QString().setNum(mu, 'g', 3) + "\n" +
                                            "Расчитываемые параметры\nСМО:\n" +
                                            "p[otk] = " + QString().setNum(p_otk, 'g', 3) + "\n" +
                                            "p[obs] = " + QString().setNum(p_obs, 'g', 3) + "\n" +
                                            "n[3] = " + QString().setNum(n3, 'g', 3) + "\n" +
                                            "k[3] = " + QString().setNum(k3, 'g', 3) + "\n" +
                                            "A = " + QString().setNum(A, 'g', 3));
            SMO_p1[this_output] = p_otk;
            SMO_p2[this_output] = p_obs;
            SMO_p3[this_output] = n3;
            SMO_p4[this_output] = k3;
            SMO_p5[this_output] = A;
        }

        SMO_names[this_output] = "СМО '" + T_name->toPlainText() + "'";
        SMO_mode[this_output] = mode;
        SMO_n[this_output] = n;
        SMO_lambda[this_output] = lambda;
        SMO_mu[this_output] = mu;

        name_outputs[this_output] = T_name->toPlainText();
        mode_outputs[this_output] = mode;
        n_outputs[this_output] = n;
        lambda_outputs[this_output] = lambda;
        mu_outputs[this_output] = mu;
        if (mode == 0) {
            m_outputs[this_output] = m;
        } else {
            m_outputs[this_output] = 0;
        }
        if (this_output >= k) {
            ++this_output;
            ++k;
            name_outputs.resize(k + 1);
            mode_outputs.resize(k + 1);
            n_outputs.resize(k + 1);
            lambda_outputs.resize(k + 1);
            mu_outputs.resize(k + 1);
            m_outputs.resize(k + 1);
        }
        B_compare->setEnabled(1);

    } else {

        QMessageBox::critical(NULL,QObject::tr("Неправильно введены данные"),tr("n и m - целые числа\nlambda и mu - вещественные числа"));

    }

}

MainWindow::~MainWindow()
{

}

CompareDialog::CompareDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowIcon(QIcon("C:/Users/Andrey/Documents/Qt Creator projects/ISMO_final/icons/Comparison.png"));
    setFixedSize(1100, 600);

    SMO_in_tables.resize(100);
    for (int i = 0; i < 100; ++i) {
        SMO_in_tables[i] = 0;
    }

    B_add = new QPushButton("Добавить СМО", this);
    B_add->setGeometry(10, 10, 300, 40);
    B_add->setStyleSheet("font-size: 16px");

    combo = new QComboBox(this);
    combo->setGeometry(320, 10, 200, 40);
    combo->setStyleSheet("font-size: 16px");
    for (int i = 0; i < k; ++i) {
        combo->addItem(SMO_names[i]);
    }

    B_export = new QPushButton("Экспортировать", this);
    B_export->setGeometry(530, 10, 200, 40);
    B_export->setStyleSheet("font-size: 16px");

    tabs = new QTabWidget(this);

    S_mode1 = new QScrollArea(this);
    S_mode1->setGeometry(0, 0, tabs->width(), 530);
    S_mode2 = new QScrollArea(this);
    S_mode2->setGeometry(0, 0, tabs->width(), 530);
    S_mode3 = new QScrollArea(this);
    S_mode3->setGeometry(0, 0, tabs->width(), 530);

    tabs->setGeometry(10, 60, this->width() - 20, 530);
    tabs->setStyleSheet("font-size: 14px");
    tabs->addTab(S_mode1, "СМО с ограниченной очередью");
    tabs->addTab(S_mode2, "СМО с неограниченной очередью");
    tabs->addTab(S_mode3, "СМО с отказами");

    Tab_mode1 = new QTableWidget(0, 8, this);
    Tab_mode1->setGeometry(0, 0, tabs->width() - 30, 50);
    Tab_mode1->setStyleSheet("font-size: 14px");
    Tab_mode1->setEditTriggers(QAbstractItemView::EditTriggers(0));
    Tab_mode2 = new QTableWidget(0, 7, this);
    Tab_mode2->setGeometry(0, 0, tabs->width() - 30, 50);
    Tab_mode2->setStyleSheet("font-size: 14px");
    Tab_mode2->setEditTriggers(QAbstractItemView::EditTriggers(0));
    Tab_mode3 = new QTableWidget(0, 8, this);
    Tab_mode3->setGeometry(0, 0, tabs->width() - 30, 50);
    Tab_mode3->setStyleSheet("font-size: 14px");
    Tab_mode3->setEditTriggers(QAbstractItemView::EditTriggers(0));

    Tab_mode1->setColumnWidth(0, 100);
    Tab_mode2->setColumnWidth(0, 120);
    Tab_mode3->setColumnWidth(0, 120);

    Tab_mode1->setHorizontalHeaderLabels(QStringList() <<"Каналы\nобслуживания"<<"Интенсивность\nзаявок"<<"Интенсивность\nобслуживания"<<"Размер очереди"<<"Вероятность\n отказа"<<"Вероятность\nобслуживания"<<"Заявок в   \nочереди"<<"Среднее время\nожидания");
    Tab_mode2->setHorizontalHeaderLabels(QStringList() <<"Каналы\nобслуживания"<<"Интенсивность\nзаявок"<<"Интенсивность\nобслуживания"<<"Вероятность \nочереди"<<"Размер\n очереди"<<"Заявки на\n обслуживании"<<"Время\nзаявки в СМО");
    Tab_mode3->setHorizontalHeaderLabels(QStringList() <<"Каналы\nобслуживания"<<"Интенсивность\nзаявок"<<"Интенсивность\nобслуживания"<<"Вероятность \nотказа"<<"Вероятность\nобслуживания"<<"Среднее число\nканалов СМО"<<"Коэффициент\nзагрузки"<<"Пропускная\nспособность");

    for (int i = 0; i < 8; ++i) {
        Tab_mode1->setColumnWidth(i, 110);
        Tab_mode3->setColumnWidth(i, 110);
        if (i < 7) {
            Tab_mode2->setColumnWidth(i, 110);
        }
    }

    S_mode1->setWidget(Tab_mode1);
    S_mode2->setWidget(Tab_mode2);
    S_mode3->setWidget(Tab_mode3);

    createConnections();

}

void CompareDialog::createConnections() {
    connect(B_add, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(B_export, SIGNAL(clicked()), this, SLOT(slotButton()));
}

void CompareDialog::slotButton() {
    if (sender() == B_add) {
        int t = combo->currentIndex();
        if (SMO_in_tables[t] == 0) {
            if (SMO_mode[combo->currentIndex()] == 0) {

                Tab_mode1->setRowCount(k1 + 1);

                QTableWidgetItem *item;
                item = new QTableWidgetItem;
                item->setText(combo->currentText());
                Tab_mode1->setVerticalHeaderItem(k1, item);

                QTableWidgetItem *item1;
                item1 = new QTableWidgetItem;
                item1->setText(QString().number(SMO_n[t]));
                Tab_mode1->setItem(k1, 0, item1);

                QTableWidgetItem *item2;
                item2 = new QTableWidgetItem;
                item2->setText(QString().setNum(SMO_lambda[t], 'g', 3));
                Tab_mode1->setItem(k1, 1, item2);

                QTableWidgetItem *item3;
                item3 = new QTableWidgetItem;
                item3->setText(QString().setNum(SMO_mu[t], 'g', 3));
                Tab_mode1->setItem(k1, 2, item3);

                QTableWidgetItem *item4;
                item4 = new QTableWidgetItem;
                item4->setText(QString().number(SMO_m[t]));
                Tab_mode1->setItem(k1, 3, item4);

                QTableWidgetItem *item5;
                item5 = new QTableWidgetItem;
                item5->setText(QString().setNum(SMO_p1[t], 'g', 3));
                Tab_mode1->setItem(k1, 4, item5);

                QTableWidgetItem *item6;
                item6 = new QTableWidgetItem;
                item6->setText(QString().setNum(SMO_p2[t], 'g', 3));
                Tab_mode1->setItem(k1, 5, item6);

                QTableWidgetItem *item7;
                item7 = new QTableWidgetItem;
                item7->setText(QString().setNum(SMO_p3[t], 'g', 3));
                Tab_mode1->setItem(k1, 6, item7);

                QTableWidgetItem *item8;
                item8 = new QTableWidgetItem;
                item8->setText(QString().setNum(SMO_p4[t], 'g', 3));
                Tab_mode1->setItem(k1, 7, item8);

                ++k1;
                Tab_mode1->setGeometry(0, 0, tabs->width(), 50 + k1 * 30);

            } else if (SMO_mode[combo->currentIndex()] == 1) {

                Tab_mode2->setRowCount(k2 + 1);

                QTableWidgetItem *item;
                item = new QTableWidgetItem;
                item->setText(combo->currentText());
                Tab_mode2->setVerticalHeaderItem(k2, item);

                QTableWidgetItem *item1;
                item1 = new QTableWidgetItem;
                item1->setText(QString().number(SMO_n[t]));
                Tab_mode2->setItem(k2, 0, item1);

                QTableWidgetItem *item2;
                item2 = new QTableWidgetItem;
                item2->setText(QString().setNum(SMO_lambda[t], 'g', 3));
                Tab_mode2->setItem(k2, 1, item2);

                QTableWidgetItem *item3;
                item3 = new QTableWidgetItem;
                item3->setText(QString().setNum(SMO_mu[t], 'g', 3));
                Tab_mode2->setItem(k2, 2, item3);

                QTableWidgetItem *item5;
                item5 = new QTableWidgetItem;
                item5->setText(QString().setNum(SMO_p1[t], 'g', 3));
                Tab_mode2->setItem(k2, 3, item5);

                QTableWidgetItem *item6;
                item6 = new QTableWidgetItem;
                item6->setText(QString().setNum(SMO_p2[t], 'g', 3));
                Tab_mode2->setItem(k2, 4, item6);

                QTableWidgetItem *item7;
                item7 = new QTableWidgetItem;
                item7->setText(QString().setNum(SMO_p3[t], 'g', 3));
                Tab_mode2->setItem(k2, 5, item7);

                QTableWidgetItem *item8;
                item8 = new QTableWidgetItem;
                item8->setText(QString().setNum(SMO_p4[t], 'g', 3));
                Tab_mode2->setItem(k2, 6, item8);

                ++k2;
                Tab_mode2->setGeometry(0, 0, tabs->width(), 50 + k2 * 30);

            } else {

                Tab_mode3->setRowCount(k3 + 1);

                QTableWidgetItem *item;
                item = new QTableWidgetItem;
                item->setText(combo->currentText());
                Tab_mode3->setVerticalHeaderItem(k3, item);

                QTableWidgetItem *item1;
                item1 = new QTableWidgetItem;
                item1->setText(QString().number(SMO_n[t]));
                Tab_mode3->setItem(k3, 0, item1);

                QTableWidgetItem *item2;
                item2 = new QTableWidgetItem;
                item2->setText(QString().setNum(SMO_lambda[t], 'g', 3));
                Tab_mode3->setItem(k3, 1, item2);

                QTableWidgetItem *item3;
                item3 = new QTableWidgetItem;
                item3->setText(QString().setNum(SMO_mu[t], 'g', 3));
                Tab_mode3->setItem(k3, 2, item3);

                QTableWidgetItem *item5;
                item5 = new QTableWidgetItem;
                item5->setText(QString().setNum(SMO_p1[t], 'g', 3));
                Tab_mode3->setItem(k3, 3, item5);

                QTableWidgetItem *item6;
                item6 = new QTableWidgetItem;
                item6->setText(QString().setNum(SMO_p2[t], 'g', 3));
                Tab_mode3->setItem(k3, 4, item6);

                QTableWidgetItem *item7;
                item7 = new QTableWidgetItem;
                item7->setText(QString().setNum(SMO_p3[t], 'g', 3));
                Tab_mode3->setItem(k3, 5, item7);

                QTableWidgetItem *item8;
                item8 = new QTableWidgetItem;
                item8->setText(QString().setNum(SMO_p4[t], 'g', 3));
                Tab_mode3->setItem(k3, 6, item8);

                QTableWidgetItem *item9;
                item9 = new QTableWidgetItem;
                item9->setText(QString().setNum(SMO_p5[t], 'g', 3));
                Tab_mode3->setItem(k3, 7, item9);

                ++k3;
                Tab_mode3->setGeometry(0, 0, tabs->width(), 50 + k3 * 30);

            }
            SMO_in_tables[t] = 1;
        }
    }
    if (sender() == B_export) {
        QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "./", tr("matr(*.csv)"));
        QString suf = QFileInfo(filename).suffix();
        if (suf.isEmpty()) filename.append(".csv");
        QFile f(filename);
        if(f.open(QIODevice::WriteOnly)) {
                QTextStream ts( &f );
                QStringList strList;

                strList<<"\" \"";

                for(int c = 0; c < Tab_mode1->horizontalHeader()->count(); ++c)
                    strList<<"=\"" + Tab_mode1->model()->headerData(c, Qt::Horizontal).toString()+"\"";
                ts<<strList.join( ";" )+"\n";
                for(int r = 0; r < Tab_mode1->verticalHeader()->count(); ++r)
                {
                    strList.clear();
                    strList<<"=\"" + Tab_mode1->model()->headerData(r, Qt::Vertical).toString() + "\"";
                    for( int c = 0; c < Tab_mode1->horizontalHeader()->count(); ++c )
                    {
                        strList<<"=\"" + Tab_mode1->model()->data(Tab_mode1->model()->index(r, c), Qt::DisplayRole).toString() + "\"";
                    }
                    if (r != Tab_mode1->verticalHeader()->count() - 1) {
                        ts<<strList.join(";") + "\n";
                    }
                }

                strList<<"\n\n\" \"";

                for(int c = 0; c < Tab_mode2->horizontalHeader()->count(); ++c)
                    strList<<"=\"" + Tab_mode2->model()->headerData(c, Qt::Horizontal).toString()+"\"";
                ts<<strList.join( ";" )+"\n";
                for(int r = 0; r < Tab_mode2->verticalHeader()->count(); ++r)
                {
                    strList.clear();
                    strList<<"=\"" + Tab_mode2->model()->headerData(r, Qt::Vertical).toString() + "\"";
                    for( int c = 0; c < Tab_mode2->horizontalHeader()->count(); ++c )
                    {
                        strList<<"=\"" + Tab_mode2->model()->data(Tab_mode2->model()->index(r, c), Qt::DisplayRole).toString() + "\"";
                    }
                    if (r != Tab_mode2->verticalHeader()->count() - 1) {
                        ts<<strList.join(";") + "\n";
                    }
                }

                strList<<"\n\n\" \"";

                for(int c = 0; c < Tab_mode3->horizontalHeader()->count(); ++c)
                    strList<<"=\"" + Tab_mode3->model()->headerData(c, Qt::Horizontal).toString()+"\"";
                ts<<strList.join( ";" )+"\n";
                for(int r = 0; r < Tab_mode3->verticalHeader()->count(); ++r)
                {
                    strList.clear();
                    strList<<"=\"" + Tab_mode3->model()->headerData(r, Qt::Vertical).toString() + "\"";
                    for( int c = 0; c < Tab_mode3->horizontalHeader()->count(); ++c )
                    {
                        strList<<"=\"" + Tab_mode3->model()->data(Tab_mode3->model()->index(r, c), Qt::DisplayRole).toString() + "\"";
                    }
                    ts<<strList.join(";") + "\n";
                }

                f.close();
            }
    }
}

CompareDialog::~CompareDialog()
{

}
