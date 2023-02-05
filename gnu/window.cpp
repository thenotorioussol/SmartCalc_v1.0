#include "window.h"

Dialog::Dialog(QWidget *parent)
                : QDialog(parent)
                , ui(new Ui::Dialog) {
    ui->setupUi(this);
    ui->x_text->setText("0");
    connect(this->ui->btn_0, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_1, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_2, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_3, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_4, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_5, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_6, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_7, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_8, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_9, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_mnoj, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_plus, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_minus, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_div, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_point, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_cos, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_sin, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_tan, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_asin, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_acos, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_atan, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_open, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_close, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_ln, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_log, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_sqrt, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_pow, SIGNAL(clicked(bool)), this, SLOT(click_btns()));
    connect(this->ui->btn_x, SIGNAL(clicked(bool)), this, SLOT(click_btns()));

    connect(this->ui->btn_graph, SIGNAL(clicked(bool)), this, SLOT(click_btn_graph()));
    connect(this->ui->btn_result, SIGNAL(clicked(bool)), this, SLOT(click_btn_result()));
    connect(this->ui->btn_clean, SIGNAL(clicked(bool)), this, SLOT(click_btn_clean()));
    connect(this->ui->btn_clean_all, SIGNAL(clicked(bool)), this, SLOT(click_btn_clean_all()));

    connect(this->ui->btn_clean_credit, SIGNAL(clicked(bool)), this, SLOT(click_btn_clean_credit()));
    connect(this->ui->btn_diff, SIGNAL(clicked(bool)), this, SLOT(click_credit_result()));
    connect(this->ui->btn_annuity, SIGNAL(clicked(bool)), this, SLOT(click_credit_result()));

    connect(this->ui->btn_clean_deposite, SIGNAL(clicked(bool)), this, SLOT(click_btn_clean_deposite()));
    connect(this->ui->btn_cap, SIGNAL(clicked(bool)), this, SLOT(click_deposite_result()));
    connect(this->ui->btn_nocap, SIGNAL(clicked(bool)), this, SLOT(click_deposite_result()));

    this->str = "";
}

Dialog::~Dialog() {
    delete ui;
}

void Dialog::click_btn_clean_credit() {
    this->str = "";
    this->ui->input_amount->setText(this->str);
    this->ui->input_rate->setText(this->str);
    this->ui->input_term->setText(this->str);
    this->ui->out_month->setText(this->str);
    this->ui->out_over->setText(this->str);
    this->ui->out_total->setText(this->str);
}

void Dialog::click_credit_result() {
    int dif = 0;
    QPushButton *button = (QPushButton*)sender();
    if (button->text() == "differentiated") dif = 1;
    QByteArray bA = this->ui->input_amount->toPlainText().toLocal8Bit();
    char *amount = bA.data();
    QByteArray bB = this->ui->input_rate->toPlainText().toLocal8Bit();
    char *rate = bB.data();
    QByteArray bC = this->ui->input_term->toPlainText().toLocal8Bit();
    char *term = bC.data();
    int error = 0;
    t_credit result = do_credit(amount, rate, term, &error, dif);
    if (error) {
        this->ui->error_credit->setText("ERROR");
    } else {
        QString month = QString::number(result.paymentOne);
        if (dif) month += " - " + QString::number(result.paymentLast);
        QString over = QString::number(result.overpayment);
        QString total = QString::number(result.total);
        this->ui->out_month->setText(month);
        this->ui->out_over->setText(over);
        this->ui->out_total->setText(total);
    }
}

void Dialog::click_btn_clean_deposite() {
    this->str = "";
    this->ui->deposite_amount->setText(this->str);
    this->ui->deposite_rate->setText(this->str);
    this->ui->deposite_term->setText(this->str);
    this->ui->tax_rate->setText(this->str);
    this->ui->regularity->setText(this->str);
    this->ui->sum_percent->setText(this->str);
    this->ui->tax_sum->setText(this->str);
    this->ui->deposite_total->setText(this->str);
}

void Dialog::click_deposite_result() {
    int cap = 0;
    QPushButton *button = (QPushButton*)sender();
    if (button->text() == "interest capitalization") cap = 1;
    QByteArray bA = this->ui->deposite_amount->toPlainText().toLocal8Bit();
    char *amount = bA.data();
    QByteArray bB = this->ui->deposite_rate->toPlainText().toLocal8Bit();
    char *rate = bB.data();
    QByteArray bC = this->ui->deposite_term->toPlainText().toLocal8Bit();
    char *term = bC.data();
    QByteArray bD = this->ui->tax_rate->toPlainText().toLocal8Bit();
    char *tax = bD.data();
    QByteArray bE = this->ui->regularity->toPlainText().toLocal8Bit();
    char *regularity = bE.data();
    int error = 0;
    t_deposit result = do_deposit(amount, term, rate, tax, regularity, cap, &error);
    if (error) {
        this->ui->error_deposite->setText("ERROR");
    } else {
        QString sumPer = QString::number(result.percentSum);
        QString taxSum = QString::number(result.taxSum);
        QString total = QString::number(result.totalSum);
        this->ui->sum_percent->setText(sumPer);
        this->ui->tax_sum->setText(taxSum);
        this->ui->deposite_total->setText(total);
    }
}

void Dialog::click_btn_clean() {
    this->str = this->ui->txt_input->toPlainText();
    this->str.resize(this->str.size() - 1);
    this->ui->txt_input->setText(this->str);
    QTextCursor cursor = this->ui->txt_input->textCursor();
    cursor.movePosition(QTextCursor::End);
    this->ui->txt_input->setTextCursor(cursor);
}

void Dialog::click_btn_clean_all() {
    this->str = "";
    this->ui->txt_input->setText(this->str);
    this->ui->txt_output->setText(this->str);
    ui->x_text->setText("0");
}

void Dialog::click_btn_result() {
    int error = 0;
    this->str = this->ui->txt_input->toPlainText();
    QByteArray bA = this->str.toLocal8Bit();
    char request[257];
    snprintf(request, sizeof(request), " %s", bA.data());
    this->str = this->ui->x_text->toPlainText();
    bA = this->str.toLocal8Bit();
    char *x_t = bA.data();
    QString result = QString::number(do_calc(request, x_t, &error));
    if (error) result = "ERROR";
    this->ui->txt_output->setText(result);
}

void Dialog::click_btn_graph() {
    this->ui->txt_output->setText("");
    int error = 0;
    graphic neww = graph_info(&error);
    if (error || neww.x_max <= neww.x_min) {
        this->ui->txt_output->setText("ERROR");
        return;
    } else {
        this->ui->txt_output->setText("");
    }
    QGraphicsScene *scence = new QGraphicsScene(ui->graphicsView);
    QPen graph_line(Qt::blue);
    grip_render(scence, neww);
    double x = neww.x_min, move_x = 0.02;
    double y0 = do_graph(neww.request, x / neww.scale, neww.scale) - neww.res_0;
    for (int count = -neww.width * 50; count <= neww.width * 50; count++, x += move_x) {
        double y1 = do_graph(neww.request, (x + move_x) / neww.scale, neww.scale) - neww.res_0;
        if (y0 <= neww.height && y0 >= -neww.height && y1 <= neww.height && y1 >= -neww.height) {
            scence->addLine(x, -y0, x + move_x, -y1, graph_line);
        }
        y0 = y1;
    }
    ui->graphicsView->setScene(scence);
    this->ui->tabWidget->setCurrentIndex(1);
}

graphic Dialog::graph_info(int *error) {
    graphic neww;
    num_of_grid = this->ui->spinBox->value() + 1;
    this->str = this->ui->txt_input->toPlainText();
    QByteArray bA = this->str.toLocal8Bit();
    snprintf(neww.request, sizeof(neww.request), " %s", bA.data());
    this->str = this->ui->x_max->toPlainText();
    bA = this->str.toLocal8Bit();
    sscanf(bA, " %lf", &neww.x_max);
    this->str = this->ui->x_min->toPlainText();
    bA = this->str.toLocal8Bit();
    sscanf(bA, " %lf", &neww.x_min);
    neww.width = (this->ui->graphicsView->width() - 4) / 2;
    neww.height = (this->ui->graphicsView->height() - 4) / 2;
    char x_text[256];
    sprintf(x_text, "%lf", (neww.x_max + neww.x_min) / 2);
    neww.res_0 = do_calc(neww.request, x_text, error);
    int count = 0;
    while (!isfinite(neww.res_0) && count < 1e8) {
        if (count < 1e2) count++;
        else if (count < 1e6) count *= 5;
        else count *= 10;
        double res_0_a = do_graph(neww.request, (neww.x_max + neww.x_min) / 2 + count, 1);
        double res_0_b = do_graph(neww.request, (neww.x_max + neww.x_min) / 2 - count, 1);
        if (!isnormal(res_0_a) && isnormal(res_0_b)) res_0_a = 0;
        if (!isnormal(res_0_b) && isnormal(res_0_a)) res_0_b = 0;
        neww.res_0 = (res_0_a + res_0_b) / 2;
    }
    if (!isfinite(neww.res_0)) neww.res_0 = 0;
    if (!neww.x_min && !neww.x_max) {
        neww.x_max += fabs(neww.res_0) + 2 * M_PI + count;
        neww.x_min -= fabs(neww.res_0) + 2 * M_PI + count;
        neww.res_0 = 0;
    } else if (fabs(neww.res_0) < neww.x_max / 2) {
        neww.res_0 = 0;
    }
    neww.scale = 2 * neww.width / (neww.x_max - neww.x_min);
    neww.x_max *= neww.scale;
    neww.x_min *= neww.scale;
    neww.res_0 *= neww.scale;
    return neww;
}

void Dialog::grip_render(QGraphicsScene *scence, graphic neww) {
    QPen grid_line(Qt::black);
    QPen axis_line(Qt::black);
    axis_line.setWidthF(1.5);
    scence->addLine(neww.x_min, neww.height, neww.x_max, neww.height, axis_line);
    scence->addLine(neww.x_min, -neww.height, neww.x_min, neww.height, axis_line);

    char grid_txt[16];
    double grid_move = 2 * neww.width / num_of_grid;
    double grid_p = neww.x_min + grid_move;
    for (int count = 1; count < num_of_grid; count++, grid_p += grid_move) {
        if (fabs(grid_p / neww.scale) < 1e-10) {
            grid_line.setWidthF(1.5);
            grid_p = 0;
        } else {
            grid_line.setWidthF(0.5);
        }
        if (fabs(grid_p / neww.scale) > 1e4 || \
           (fabs(grid_p / neww.scale) < 1e-4 && fabs(grid_p / neww.scale) > 1e-10))
            snprintf(grid_txt, sizeof(grid_txt), grid_accuracy_e, grid_p / neww.scale);
        else
            snprintf(grid_txt, sizeof(grid_txt), grid_accuracy_f, grid_p / neww.scale);
        QGraphicsTextItem *x_p = new QGraphicsTextItem(grid_txt);
        x_p->setPos(grid_p, neww.height - 23);
        scence->addLine(grid_p, -neww.height, grid_p, neww.height, grid_line);
        scence->addLine(grid_p, neww.height - 10, grid_p, neww.height, axis_line);
        scence->addItem(x_p);
    }

    grid_move = 2 * neww.height / num_of_grid;
    grid_p = neww.height - grid_move;
    for (int count = num_of_grid; count > 1; count--, grid_p -= grid_move) {
        if (fabs((-grid_p + neww.res_0) / neww.scale) < 1e-10) {
            grid_p = -0.0 + neww.res_0;
            grid_line.setWidthF(1.5);
        } else {
            grid_line.setWidthF(0.5);
        }
        if (fabs((-grid_p + neww.res_0) / neww.scale) > 1e4 || \
           (fabs((-grid_p + neww.res_0) / neww.scale) < 1e-4 && \
           fabs((-grid_p + neww.res_0) / neww.scale) > 1e-10))
            snprintf(grid_txt, sizeof(grid_txt), grid_accuracy_e, (-grid_p + neww.res_0) / neww.scale);
        else
            snprintf(grid_txt, sizeof(grid_txt), grid_accuracy_f, (-grid_p + neww.res_0) / neww.scale);
        QGraphicsTextItem *y_p = new QGraphicsTextItem(grid_txt);
        y_p->setPos(neww.x_min + 7, grid_p);
        scence->addLine(neww.x_min, grid_p, neww.x_max, grid_p, grid_line);
        scence->addLine(neww.x_min, grid_p, neww.x_min + 10, grid_p, axis_line);
        scence->addItem(y_p);
    }
}

void Dialog::click_btns() {
    QPushButton *button = (QPushButton*)sender();
    this->ui->txt_input->insertPlainText(button->text());
}
