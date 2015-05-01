
function addParam(e) {
    var name=$('#name').val(),value=$('#value').val();
    $('#testinputs').append('<div>'+name+': <input name="'+name+'" value="'+value+'" /><span class="remove">X</span></div>');
    $('.remove').click(removeParam);
}

function send(e) {
    var host=$('#host').val(),port=$('#port').val(),
            action='http://'+host;
    //alert(action);
    $('#httpform').attr('action',action);
    $('#httpform').submit();
}

function removeParam(e) {
    $(this).parent().remove();
}

$(function () {
   $('#add-param').click(addParam) ;
   $('#submit').click(send);
  
});