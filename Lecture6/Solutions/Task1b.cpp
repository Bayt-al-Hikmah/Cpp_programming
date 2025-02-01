#include <iostream>
using namespace std;

#define MAX_APPLICATIONS 20
using Worker = unsigned;
using Application = struct Application{
Worker worker;
struct Application *next;
};

void apply(Application *app, int worker_number, int counter);
void hire(Application **app);
void free_application(Application* app);

int main(){
    Application *application;
    application = new Application;
    application->next = NULL;
    application->worker = 0;
    apply(application, 1, 0);
    apply(application, 1, 0);
    hire(&application);
    apply(application, 1, 0);
    apply(application, 1, 0);
    hire(&application);
    hire(&application);
    free_application(application);
    return 0;
}
void apply(Application *app, int worker_number, int counter){
    if(counter >= MAX_APPLICATIONS){
        cout << "Applications are full!\n";
        return;
    }else if(app->next == NULL && app->worker == 0){
        app->worker = worker_number;
        cout << "Person "<< app->worker << " Applied to the job!\n";
        app->next = new Application;
        app = app->next;
        app->next = NULL;
        app->worker = 0;
        
        return ;

    }
    apply(app->next, app->worker + 1, counter + 1);   
}
void hire(Application **app){
    Application *tmp = *app;
    if ((*app)->next == NULL && (*app)->worker == 0){
        cout << "Applications Empty !\n";
        return ;
    }
    cout << "Hired Worker " << (*app)->worker << "!\n";
    (*app) = (*app)->next;

    delete tmp;
    return ;
}
void free_application(Application* app){
if (app->next == NULL && app->worker == 0){
        delete app;
        return ;
    }
    free_application(app->next);
    delete app;
    return;
}