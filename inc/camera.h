sf::View calcViewWhenResized(const sf::Vector2u &windowsize, const sf::Vector2u &designedsize){
	sf::FloatRect viewport(0.f, 0.f, 1.f, 1.f);

	float screenwidth = windowsize.x / static_cast<float>(designedsize.x);
	float screenheight = windowsize.y / static_cast<float>(designedsize.y);

	if(screenwidth > screenheight){
		viewport.width = screenheight / screenwidth;
		viewport.left = (1.f - viewport.width) / 2.f;
	}
	else if(screenwidth < screenheight){
		viewport.height = screenwidth / screenheight;
		viewport.top = (1.f - viewport.height) / 2.f;
	}

	sf::View view( sf::FloatRect( 0, 0, designedsize.x , designedsize.y ) );
	view.setViewport(viewport);

	return view;
}

sf::View calcViewOnPlayerMovement(sf::View view, Player* player, Livello* level, int windowWidth, int windowHeight){
	int xDisegnata, yDisegnata;
	
	if (player->x+(player->width/2) < windowWidth/2){
		xDisegnata=0;
	} else {
		if (player->x + (player->width/2) > level->maxWidth-windowWidth/2 ) {
			xDisegnata = level->maxWidth - windowWidth;	
		} else {
			xDisegnata = (player->x+player->width/2)-windowWidth/2;
		} 
	}
      	
	if (player->y < windowHeight/2){
		yDisegnata = 0;
	} else {
		if (player->y + player->height/2 > level->maxHeight-windowHeight/2){
			yDisegnata = level->maxHeight - windowHeight;
		} else {
			yDisegnata = player->y+player->height/2 - windowHeight/2;
		}
	}

	view.setCenter(xDisegnata+windowWidth/2, yDisegnata+windowHeight/2);
	return view;
}
