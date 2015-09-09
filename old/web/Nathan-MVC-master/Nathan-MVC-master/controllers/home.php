<?php
/* 
 * Project: Nathan MVC
 * File: /controllers/home.php
 * Purpose: controller for the home of the app.
 * Author: Nathan Davison
 */

class HomeController extends BaseController
{
    //add to the parent constructor
    public function __construct($action, $urlValues) {
        parent::__construct($action, $urlValues);
        
        //create the model object
        require("models/home.php");
        $this->model = new HomeModel();
    }
    
    //default method
    protected function index()
    {
        $this->view->output($this->model->index());
    }
}

?>
