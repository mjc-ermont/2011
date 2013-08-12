$(function(){
    
});

function switchShield(p){
    $(".dynamic-show>.img>img").hide();
    $(".dynamic-show>.img>." + p).show();
    
    $(".dynamic-show>.description").hide();
    $(".dynamic-show>.description." + p).show();
}