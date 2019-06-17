#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "QThread"
#include "QDateTime"
#include "QTime"

class Sleeper: public QThread
{
public:
    static void msleep(unsigned long ms)
        {
            QThread::msleep(ms);
        }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        popUp = new PopUp();

        ui->Projects->toggle();
        close_all_widgets();

        timerId = startTimer(1000);

        search_and_clean_in_files("plans.txt");
        search_and_clean_in_files("meetings.txt");
        search_and_clean_in_files("reminds.txt");

        get_plans();
        get_reminds();
        get_meetings();



        ui->ToDo_Area->setLayout(new QVBoxLayout);
        ui->ToDo_Area->setWidgetResizable(true);

        QWidget* temp = new QWidget;
        temp->setLayout(new QVBoxLayout);
        ui->ToDo_Area->setWidget(temp);

        get_todo();
        All_Browser_Update();

        Sleeper::msleep(1000);
        notifications();
    }

void MainWindow::timerEvent(QTimerEvent *evt)
{
    if (evt->timerId() == timerId)
        {
            QTime currTime = QTime::currentTime();
            ui->CurrentTime->setText(currTime.toString("hh:mm:ss"));
        }
}

void MainWindow::close_all_widgets()
{
     ui->Daily_Planner_Widget->hide();
     ui->Reminds_Widget->hide();
     ui->Meetings_Widget->hide();
     ui->Shopping_Lists_Widget->hide();
     ui->ToDo_Lists_Widget->hide();

    /*
     ui->shopping_lists->hide();
     ui->todo_lists->hide();//*/
     ui->Shopping_Lists_Widget->setEnabled(false);
     ui->Meetings_Widget->setEnabled(false);
     ui->Reminds_Widget->setEnabled(false);
     ui->Daily_Planner_Widget->setEnabled(false);
     ui->ToDo_Lists_Widget->setEnabled(false);
}

MainWindow::~MainWindow()
    {
        delete ui;
        killTimer(timerId);
    }

void MainWindow::on_Projects_clicked()
    {
       close_all_widgets();
       ui->Overwiew->toggle();
       ui->Projects->toggle();
    }

void MainWindow::on_DailyPlanner_clicked()
    {
         close_all_widgets();
         ui->Daily_Planner_Widget->show();
         ui->Daily_Planner_Widget->setEnabled(true);
         ui->Calendar_2->setSelectedDate(QDate::currentDate());
         ui->PlanDateEdit->setDate(QDate::currentDate());
         ui->PlanTimeEdit->setTime(QTime::currentTime());
    }

void MainWindow::on_Reminders_clicked()
    {
        close_all_widgets();
        ui->RemindDateEdit->setDate(QDate::currentDate());
        ui->RemindTimeEdit->setTime(QTime::currentTime());
        ui->Reminds_Widget->show();
        ui->Reminds_Widget->setEnabled(true);
    }

void MainWindow::on_Meetings_clicked()
    {
        close_all_widgets();
        ui->MeetingDateEdit->setDate(QDate::currentDate());
        ui->MeetingTimeEdit->setTime(QTime::currentTime());
        ui->Meetings_Widget->show();
        ui->Meetings_Widget->setEnabled(true);
    }

void MainWindow::on_ShoppingLists_clicked()
    {
        close_all_widgets();
        ui->Shopping_Lists_Widget->show();
        ui->Shopping_Lists_Widget->setEnabled(true);
        get_FILE_NAME()="list.txt";
        save("");
    }

void MainWindow::on_ToDoLists_clicked()
    {
        close_all_widgets();
        ui->ToDo_Lists_Widget->show();
        ui->ToDo_Lists_Widget->setEnabled(true);
    }

QString get_style_sheet(int status)
{
    if (status==0)
        {
            return "color: rgb(0, 0, 0);\nbackground-image: url(:/images/icons/urgent_icon.png);";
        }
    if (status==1)
        {
            return "color: rgb(0, 0, 0);\nbackground-image: url(:/images/icons/in_progress_icon.png);";
        }
    if (status==2)
        {
            return "color: rgb(0, 0, 0);\nbackground-image: url(:/images/icons/done_icon.png);";
        }
    return "";
}

void MainWindow::All_Browser_Update()
{
   for(auto i = plans.begin();i!=plans.end();i++)
       {
             ui->Plans_Browser->append(i->print());
       }
   for(auto i = reminds.begin();i!=reminds.end();i++)
       {
             ui->Remind_Browser->append(i->print());
       }
   for(auto i = meetings.begin();i!=meetings.end();i++)
       {
             ui->Meeting_Browser->append(i->print());
       }
   for(auto i = todo_list.begin();i!=todo_list.end();i++)
       {
             ToDo_Button* button =new ToDo_Button(i->get_description(),i.value());
             button->setStyleSheet(get_style_sheet(i->get_status()));
             ui->ToDo_Area->widget()->layout()->addWidget(button);
             connect(button,SIGNAL(clicked()),this,SLOT(change_button_style()));
       }
}

void MainWindow::on_ClearProduct_clicked()
{
    ui->ProductName->clear();
    ui->ProductCount->setValue(0);
}

void MainWindow::on_Add_New_Remind_clicked()
{
    get_FILE_NAME()="reminds.txt";
    if (!ui->RemindLine->text().isEmpty())
        {
            QDateTime temp;
            temp.setDate(ui->RemindDateEdit->date());
            temp.setTime(ui->RemindTimeEdit->time());

            remind new_remind(temp,ui->RemindLine->text().toUtf8());

            reminds.insert(new_remind.get_time(),new_remind);
            keeper(new_remind.print());

             ui->Remind_Browser->append(new_remind.print());
        }
    else
        {
            QMessageBox::warning(nullptr,"Warning","No description!");
        }
}

void MainWindow::on_Add_New_Plan_clicked()
{
    get_FILE_NAME()="plans.txt";
    if (!ui->PlanLine->text().isEmpty())
        {
            QDateTime temp;
            temp.setDate(ui->PlanDateEdit->date());
            temp.setTime(ui->PlanTimeEdit->time());

            plan new_plan(temp,ui->PlanLine->text().toUtf8(),ui->PlanPrority->value());

            plans.insert(new_plan.get_time(),new_plan);
            keeper(new_plan.print());

             ui->Plans_Browser->append(new_plan.print());
        }
    else
        {
            QMessageBox::warning(nullptr,"Warning","No description!");
        }
}

void MainWindow::on_Add_New_Meeting_clicked()
{
    get_FILE_NAME()="meetings.txt";
    if (!ui->MeetingLine->text().isEmpty())
        {
            QDateTime temp;
            temp.setDate(ui->MeetingDateEdit->date());
            temp.setTime(ui->MeetingTimeEdit->time());

            meeting new_meeting(temp,ui->MeetingLine->text().toUtf8());

            meetings.insert(new_meeting.get_time(),new_meeting);
            keeper(new_meeting.print());

             ui->Meeting_Browser->append(new_meeting.print());
        }
    else
        {
            QMessageBox::warning(nullptr,"Warning","No description!");
        }
}

void MainWindow::on_Calendar_2_clicked(const QDate &date)
{
    ui->PlanDateEdit->setDate(date);
}

void MainWindow::on_Calendar_2_activated(const QDate &date)
{
    ui->PlanDateEdit->setDate(date);
}

void MainWindow::on_Search_returnPressed()
{
    close_all_widgets();
    ui->Search_Browser->clear();
    for(auto i = plans.begin();i!=plans.end();i++)
        {
            if (ui->Search->text()==i->get_description())
                {
                  ui->Search_Browser->append(i->print());
                }
        }
    for(auto i = reminds.begin();i!=reminds.end();i++)
        {
            if (ui->Search->text()==i->get_description())
                {
                  ui->Search_Browser->append(i->print());
                }
        }
    for(auto i = meetings.begin();i!=meetings.end();i++)
        {
            if (ui->Search->text()==i->get_description())
                {
                  ui->Search_Browser->append(i->print());
                }
        }
}

void MainWindow::on_AddProduct_clicked()
{
    if (!ui->ProductName->text().isEmpty())
        {
            ui->Product_Browser->append(ui->ProductName->text() + " " + QString::number(ui->ProductCount->value()));
            if(!ui->ProductList_Filename->text().isEmpty())
                {
                    get_FILE_NAME()=ui->ProductList_Filename->text()+".txt";
                }
            else
                {
                    get_FILE_NAME()="list.txt";   
                }
            keeper(ui->ProductName->text() + " " + QString::number(ui->ProductCount->value()));
            ui->ProductName->clear();
            ui->ProductCount->setValue(0);
        }
    else
        {
            QMessageBox::warning(nullptr,"Warning","No description!");
        }
}

void MainWindow::on_Product_Enable_Edit_Filename_stateChanged(int arg1)
{
    ui->ProductList_Filename->setEnabled(bool(arg1));
}

void MainWindow::on_ProductList_Filename_editingFinished()
    {
         if(!ui->ProductList_Filename->text().isEmpty())
             {
                 get_FILE_NAME()=ui->ProductList_Filename->text()+".txt";
             }
         else
             {
                 get_FILE_NAME()="list.txt";
             }
         ui->Product_Browser->clear();
    }

void MainWindow::on_Products_Start_New_List_clicked()
{
    ui->Product_Browser->clear();
    int i=0;
    if (QFile::exists("Data/list.txt"))
        {
            while(QFile::exists("Data/list"+QString::number(i)+".txt"))
                {
                    i++;
                }
            ui->ProductList_Filename->setText("list"+QString::number(i)+".txt");
        }
    else
        {
            ui->ProductList_Filename->setText("list.txt");
        }
     ui->Product_Browser->clear();
}

void MainWindow::notifications()
    {
        QString temp;
        for(auto i = plans.begin();i!=plans.end();i++)
            {
                if((i.key().date().year()==QDate::currentDate().year())&&(i.key().date().month()==QDate::currentDate().month()))
                    {
                          if (i.key().date().day() == QDate::currentDate().day())
                              {
                                 temp.append("Today: " +  i->print()+"\n");
                              }
                           if (abs(i.key().date().day() - QDate::currentDate().day()) == 7)
                              {
                                   temp.append("Next week: " +  i->print()+"\n");
                              }
                   }
            }
        for(auto i = reminds.begin();i!=reminds.end();i++)
            {
            if((i.key().date().year()==QDate::currentDate().year())&&(i.key().date().month()==QDate::currentDate().month()))
                {
                    if (i.key().date().day() == QDate::currentDate().day())
                        {
                           temp.append("Today: " +  i->print()+"\n");
                        }
                     if (abs(i.key().date().day() - QDate::currentDate().day()) == 7)
                        {
                             temp.append("Next week: " +  i->print()+"\n");
                        }
               }
            }
        for(auto i = meetings.begin();i!=meetings.end();i++)
            {
            if((i.key().date().year()==QDate::currentDate().year())&&(i.key().date().month()==QDate::currentDate().month()))
                {
                    if (i.key().date().day() == QDate::currentDate().day())
                        {
                           temp.append("Today: " +  i->print()+"\n");
                        }
                    if (abs(i.key().date().day() - QDate::currentDate().day()) == 7)
                        {
                             temp.append("Next week: " +  i->print()+"\n");
                        }
               }
            }
        popUp->setPopupText(temp);
        play_signal();
        popUp->show();
    }

void MainWindow::on_Add_Business_clicked()
{
    if(!(ui->todo_description->text().isEmpty()))
        {
            business* temp = new business(ui->todo_description->text());
            todo_list.insert(temp->get_description(),*temp);

            ToDo_Button* button = new ToDo_Button(ui->todo_description->text());
            button->setStyleSheet(get_style_sheet(0));
            ui->ToDo_Area->widget()->layout()->addWidget(button);
            connect(button,SIGNAL(clicked()),this,SLOT(change_button_style()));
            delete temp;
        }
    else
        {
            QMessageBox::warning(nullptr,"Warning","No description!");
        }
    ui->todo_description->clear();
}

void MainWindow::change_button_style()
    {
         ToDo_Button* button =  (ToDo_Button*) sender();

         switch(button->get_info().get_status())
             {
                 case 0:
                     {

                        button->get_info().get_status()=1;
                        button->setStyleSheet(get_style_sheet(button->get_info().get_status()));
                        todo_list.find(button->text())->get_status()=1;
                        break;
                     }
                 case 1:
                      {
                        button->get_info().get_status()=2;
                        button->setStyleSheet(get_style_sheet( button->get_info().get_status()));
                        todo_list.find(button->text())->get_status()=2;
                        break;
                      }
                 default:
                     {
                         button->get_info().get_status()=0;
                         button->setStyleSheet(get_style_sheet( button->get_info().get_status()));
                         todo_list.find(button->text())->get_status()=0;
                     }
             }
    }

void MainWindow::on_Save_TODO_clicked()
{
        QString temp;
        if (ui->ToDoList_Filename->text().isEmpty())
            {
                get_FILE_NAME()="todo.txt";
            }
        else
            {
                if (ui->ToDoList_Filename->text().contains(".txt"))
                    {
                         get_FILE_NAME()=ui->ToDoList_Filename->text();
                    }
                else
                    {
                        get_FILE_NAME()=ui->ToDoList_Filename->text()+".txt";
                    }
            }
    for (auto i=todo_list.begin();i!=todo_list.end();i++)
        {
            temp.append(i->get_description().toUtf8()+"|"+QString::number(i->get_status())+"\n");
        }
    save(temp);
}

void MainWindow::on_Start_New_TODO_clicked()
{
    delete ui->ToDo_Area->takeWidget();     // <- Работает ли?
    QWidget* temp = new QWidget;
    temp->setLayout(new QVBoxLayout);
    ui->ToDo_Area->setWidget(temp);     // Осторожно! Возможна утечка памяти!

    if(ui->ToDoList_Load->text().isEmpty())
        {
            get_FILE_NAME()="todo.txt";
        }
    else
        {
            if (ui->ToDoList_Load->text().contains(".txt"))
                {
                     get_FILE_NAME()=ui->ToDoList_Load->text();
                }
            else
                {
                    get_FILE_NAME()=ui->ToDoList_Load->text()+".txt";
                }
        }
    QFile file ("Data/"+get_FILE_NAME());
    if (file.exists())
        {
            file.remove();
        }

}

void MainWindow::on_ToDoList_Load_returnPressed()
{
    QString str = ui->ToDoList_Load->text();
    if(str.isEmpty())
        {
            get_FILE_NAME()="todo.txt";
        }
    else
        {
            if (str.contains(".txt"))
                {
                     get_FILE_NAME()=ui->ToDoList_Load->text();
                }
            else
                {
                    get_FILE_NAME()=ui->ToDoList_Load->text()+".txt";
                }
        }
    if(str!="")
        {
            get_todo(get_FILE_NAME());
            MainWindow::on_Start_New_TODO_clicked();
            All_Browser_Update();
        }
}
