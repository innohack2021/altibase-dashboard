$(document).ready(function() {
    //Main page FullPage
	$('#fullpage').fullpage({
		//options here
		afterLoad: function(origin, destination, direction){
			//using index
			console.log(destination.index);

			if (destination.index == 1){
				$('.fixed-nav').fadeOut();
			}
			else{
				$('.fixed-nav').fadeIn();
			}
			$('.fixed-nav').find('a').removeClass('active');
			$('.fixed-nav').find('a').eq(destination.index).addClass('active');
		}
	});

});//document ready
