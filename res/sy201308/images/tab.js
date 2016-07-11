// JavaScript Document
function scrollDoor(){
}
scrollDoor.prototype = {
sd : function(menus,divs,openClass,closeClass){
var _this = this;
if(menus.length != divs.length)
{
alert("菜单层数量和内容层数量不一样!");
return false;
}
for(var i = 0 ; i < menus.length ; i++)
{
_this.$(menus[i]).value = i;
_this.$(menus[i]).onmouseover = function(){
for(var j = 0 ; j < menus.length ; j++)
{
_this.$(menus[j]).className = closeClass;
_this.$(divs[j]).style.display = "none";
}
_this.$(menus[this.value]).className = openClass;
_this.$(divs[this.value]).style.display = "block";
}
}
},
$ : function(oid){
if(typeof(oid) == "string")
return document.getElementById(oid);
return oid;
}
}
window.onload = function(){
var SDmodel = new scrollDoor();

SDmodel.sd(["a01","a02","a03"],["a011","a022","a033"],"t1","t2");
SDmodel.sd(["b01","b02"],["b011","b022"],"t01","t02");
SDmodel.sd(["c01","c02"],["c011","c022"],"t001","t002");
}
