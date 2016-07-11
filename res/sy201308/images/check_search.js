function   check()   {   
 if (document.myform.searchkey.value==""){
 alert("搜索关键词不能为空！");
 document.myform.searchkey.focus();
 return false;
 }
}