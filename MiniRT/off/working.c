int
	light_value(t_stuff *st, t_var *tv)
{
	unsigned int j;
	light lights[3];
	
	lights[0].pos.x = 0;
	lights[0].pos.y = 240;
	lights[0].pos.z = -100;
	lights[0].intensity.r = 1;
	lights[0].intensity.g = 1;
	lights[0].intensity.b = 1;
	
	lights[1].pos.x = 3200;
	lights[1].pos.y = 3000;
	lights[1].pos.z = -1000;
	lights[1].intensity.r = 0.6;
	lights[1].intensity.g = 0.7;
	lights[1].intensity.b = 1;

	lights[2].pos.x = 600;
	lights[2].pos.y = 0;
	lights[2].pos.z = -100;
	lights[2].intensity.r = 0.3;
	lights[2].intensity.g = 0.5;
	lights[2].intensity.b = 1;

	j = 0;
	while (j < 3)
	{
		light currentLight = lights[j];
		vec dist = vectorSub(&currentLight.pos, &tv->newStart);
		
		if (vectorDot(&tv->n, &dist) <= 0.0f) 
			continue;
		tv->p = sqrtf(vectorDot(&dist, &dist));
		if (tv->p <= 0.0f)
			continue;
		ray lightRay;
		lightRay.start = tv->newStart;
		lightRay.dir = vectorScale((1 / tv->p), &dist);
		bool inShadow = false;
		unsigned int k;
		k = 0;
		while (k < 3)
		{
			if (intersectRaySphere(&lightRay, &st->sp[k], tv)){
				inShadow = true;
				break;
			}
			k++;
		}
		printf("TEST %s\n", "UY");
		if (!inShadow)
		{
			float lambert = vectorDot(&lightRay.dir, &tv->n) * tv->coef;
			st->sp[tv->csp].mat.diffuse.r += lambert * currentLight.intensity.r * st->sp[tv->csp].mat.diffuse.r;
			st->sp[tv->csp].mat.diffuse.g += lambert * currentLight.intensity.g * st->sp[tv->csp].mat.diffuse.g;
			st->sp[tv->csp].mat.diffuse.b += lambert * currentLight.intensity.b * st->sp[tv->csp].mat.diffuse.b;
		}
		j++;
	}
	return (1);
}



	ray r;
	
	material materials[3];
	materials[0].diffuse.red = 1;
	materials[0].diffuse.green = 0;
	materials[0].diffuse.blue = 0;
	materials[0].reflection = 0.2;
	
	materials[1].diffuse.red = 0;
	materials[1].diffuse.green = 1;
	materials[1].diffuse.blue = 0;
	materials[1].reflection = 0.5;
	
	materials[2].diffuse.red = 0;
	materials[2].diffuse.green = 0;
	materials[2].diffuse.blue = 1;
	materials[2].reflection = 0.9;
	
	sp spheres[3]; 
	spheres[0].pos.x = 200;
	spheres[0].pos.y = 300;
	spheres[0].pos.z = 0;
	spheres[0].radius = 100;
	spheres[0].material = 0;
	
	spheres[1].pos.x = 400;
	spheres[1].pos.y = 400;
	spheres[1].pos.z = 0;
	spheres[1].radius = 100;
	spheres[1].material = 1;
	
	spheres[2].pos.x = 500;
	spheres[2].pos.y = 140;
	spheres[2].pos.z = 0;
	spheres[2].radius = 100;
	spheres[2].material = 2;
	
	light lights[3];
	
	lights[0].pos.x = 0;
	lights[0].pos.y = 240;
	lights[0].pos.z = -100;
	lights[0].intensity.red = 1;
	lights[0].intensity.green = 1;
	lights[0].intensity.blue = 1;
	
	lights[1].pos.x = 3200;
	lights[1].pos.y = 3000;
	lights[1].pos.z = -1000;
	lights[1].intensity.red = 0.6;
	lights[1].intensity.green = 0.7;
	lights[1].intensity.blue = 1;

	lights[2].pos.x = 600;
	lights[2].pos.y = 0;
	lights[2].pos.z = -100;
	lights[2].intensity.red = 0.3;
	lights[2].intensity.green = 0.5;
	lights[2].intensity.blue = 1;

	int x,y;
	char *data;
	int endian;
	long int *img;
	int sizeline;
	int bpp;

	/*if (!(img = (int *)malloc(stuff->window.width * stuff->window.height * sizeof(int))))
		return (-1);*/
	img = mlx_new_image(stuff->context, stuff->window.width, stuff->window.height);
	data = mlx_get_data_addr(img, &bpp, &sizeline, &endian);
	printf("%d, %d, %d %d\n", bpp, sizeline, endian, sizeof(long int));
	
	/*unsigned char img[3*stuff->window.width*stuff->window.height];*/

	x = 0;
	y = 0;
	while (y < stuff->window.height)
	{
		/* Set the y-coordinate of the start position of the ray */
		r.start.y = y;
		x = 0;
		while (x < stuff->window.width)
		{
			double red = 0;
			double green = 0;
			double blue = 0;
			
			int level = 0;
			double coef = 1.0;
			
			r.start.x = x;
			r.start.y = y;
			r.start.z = -2000;
			
			r.dir.x = 0;
			r.dir.y = 0;
			r.dir.z = 1;

			while ((coef > 0.0f) && (level < 25))
			{
				/* Find closest intersection */
				double t = 20000.0f;
				int currentSphere = -1;
				
				unsigned int i;
				for(i = 0; i < 3; i++){
					if(intersectRaySphere(&r, &spheres[i], &t))
						currentSphere = i;
				}
				if(currentSphere == -1) break;
				
				vec scaled = vectorScale(t, &r.dir);
				vec newStart = vectorAdd(&r.start, &scaled);
				
				/* Find the normal for this new vector at the point of intersection */
				vec n = vectorSub(&newStart, &spheres[currentSphere].pos);
				double temp = vectorDot(&n, &n);
				if(temp == 0) break;
				
				temp = 1.0f / sqrtf(temp);
				n = vectorScale(temp, &n);

				/* Find the material to determine the colour */
				material currentMat = materials[spheres[currentSphere].material];
				
				/* Find the value of the light at this point */
				unsigned int j;
				for(j=0; j < 3; j++){
					light currentLight = lights[j];
					vec dist = vectorSub(&currentLight.pos, &newStart);
					if(vectorDot(&n, &dist) <= 0.0f) continue;
					double t = sqrtf(vectorDot(&dist,&dist));
					if(t <= 0.0f) continue;
					
					ray lightRay;
					lightRay.start = newStart;
					lightRay.dir = vectorScale((1/t), &dist);
					
					/* Lambert diffusion */
					double lambert = vectorDot(&lightRay.dir, &n) * coef; 
					red += lambert * currentLight.intensity.red * currentMat.diffuse.red;
					green += lambert * currentLight.intensity.green * currentMat.diffuse.green;
					blue += lambert * currentLight.intensity.blue * currentMat.diffuse.blue;
				}
				/* Iterate over the reflection */
				coef *= currentMat.reflection;
				
				/* The reflected ray start and direction */
				r.start = newStart;
				double reflect = 2.0f * vectorDot(&r.dir, &n);
				vec tmp = vectorScale(reflect, &n);
				r.dir = vectorSub(&r.dir, &tmp);

				level++;
			}
			int rgb[3];
			rgb[0] = (int)min(red * 255.0f, 255.0f);
			rgb[1] = (int)min(green * 255.0f, 255.0f);
			rgb[2] = (int)min(blue * 255.0f, 255.0f);
			img[(x + (y * stuff->window.width))] = rgb_to_hex(rgb);
			printf("==== > %012lx\n", img[(x + (y * stuff->window.width))]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(stuff->context, stuff->window.win, img, 0, 0);
	/*saveppm("image.xpm", img, stuff->window.width, stuff->window.height);	*/