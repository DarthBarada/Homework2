#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include <QPushButton>

#include "includes/saver.h"
#include "includes/manager.h"
#include "includes/alarm.h"
#include "includes/popup.h"

struct ToDo_Button:public QPushButton
{
    business &get_info()
        {
            return info;
        }
    ToDo_Button(QString temp)
        {
            setText(temp);
            info.get_description()=temp;
            info.get_status()=0;
        }
    ToDo_Button(QString temp,business todo)
        {
            setText(temp);
            info = todo;
        }
    ToDo_Button(business todo)
        {
            setText(todo.get_description());
            info = todo;
        }
    ~ToDo_Button()
    {

    }
private:

business info;

};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow,public saver,public manager,public Alarm
{
    Q_OBJECT
public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void change_button_style();

    void on_Projects_clicked();

    void on_DailyPlanner_clicked();

    void on_Reminders_clicked();

    void on_Meetings_clicked();

    void on_ShoppingLists_clicked();

    void on_ToDoLists_clicked();

    void close_all_widgets();

// personal functions

    void timerEvent(QTimerEvent *evt);

    void All_Browser_Update();

    void on_ClearProduct_clicked();

    void on_Add_New_Remind_clicked();

    void on_Add_New_Meeting_clicked();

    void on_Add_New_Plan_clicked();

    void on_Calendar_2_clicked(const QDate &date);

    void on_Calendar_2_activated(const QDate &date);

    void on_Search_returnPressed();

    void on_AddProduct_clicked();

    void on_Product_Enable_Edit_Filename_stateChanged(int arg1);

    void on_ProductList_Filename_editingFinished();

    void on_Products_Start_New_List_clicked();

    void notifications();

    void on_Add_Business_clicked();

    void on_Save_TODO_clicked();

    void on_Start_New_TODO_clicked();

    void on_ToDoList_Load_returnPressed();

private:
    Ui::MainWindow *ui;
    int timerId;
    PopUp *popUp;       // Объявляем объект всплывающего сообщения
};

#endif // MAINWINDOW_H
