t_inter
	intersect_r_cy(t_stuff *st, void *ptr, t_inter *ti, ray *r)
{
	t_cy	cy;
	vec		p0;
	double  t0, t1;
	vec 	norm;
	int delta;
	double t2[2];

	cy = *(t_cy *)ptr;
	ti->match = true;
	normalize_vec(&cy.norm);
	n_vec(r->start.x - cy.pos.x, r->start.y- cy.pos.y, r->start.z  - cy.pos.z, &p0);
	cy.top = vectoradd(cy.pos, vectorscale(cy.len, cy.norm));
	//double a = r->dir.x * r->dir.x + r->dir.z * r->dir.z;
	//double b = 2 * (r->dir.x * p0.x +r->dir.z * p0.z);
	//double c = p0.x * p0.x + p0.z * p0.z - cy.radius * cy.radius;

	// double a = r->dir.x * r->dir.x + r->dir.z * r->dir.z;
	// double b = 2 * r->start.x * r->dir.x + 2 * r->start.z * r->dir.z;
	// double c = r->start.x * r->start.x + r->start.z * r->start.z - cy.radius * cy.radius;
	// double delta = b * b - (a * c) * 4;

	vec hit1 = vectorsub(r->start, cy.pos); // o2
	vec hit2 = vectorsub(hit1, vectorscale(vectordot(hit1, cy.norm), cy.norm)); // o4
	vec norm1 = vectorsub(cy.top, cy.pos);
	vec hit3 = vectorsub(r->dir, vectorscale(vectordot(r->dir, cy.norm), cy.norm));
	double a = vectordot(hit3, hit3);
	double b = 2 * vectordot(hit3, hit2);
	double c = vectordot(hit2, hit2) - (cy.radius * cy.radius);
	delta = b * b - (4 * a * c);
	if (a == 0)
		a = 0.00001;
	// delta < 0 means no intersections
	if (delta < EPSILON)
		return(invalid_ti(ti));
	t0 = (-b + sqrt(delta)) / (2 * a);
	t1 = (-b - sqrt(delta)) / (2 * a);	
	vec in = vectorsub(vectoradd(r->start, vectorscale(t0, r->dir)), cy.pos);
	vec out = vectorsub(vectoradd(r->start, vectorscale(t1, r->dir)), cy.pos);
	if (vectordot(in, norm1) > vectordot(norm1, norm1) || vectordot(in, norm1) < EPSILON)
		t0 = 20000000;
	if (vectordot(out, norm1) > vectordot(norm1, norm1) || vectordot(out, norm1) < EPSILON)
		t1 = 20000000;
	if(t0 > t1)
		t0 = t1;
	if (t0 > EPSILON && t0 != 20000000)
		ti->t = t0;
	else
		return(invalid_ti(ti));
	if (ti->t < 0)
		printf("TTTTT %f\n", ti->t);

	//if(t0 > t1)
	//	ft_swap(&t0, &t1);
	//ti->t = t0;
	//if ((t0 < EPSILON || t0 > (20000000 - EPSILON)))
	//	ti->t = t1;
	//if (ti->t < EPSILON || ti->t > (20000000 - EPSILON))
	//	return(invalid_ti(ti));
	//
	ti->hit =  vectoradd(r->start, vectorscale(ti->t, r->dir));
	double z = sqrt(fabs((calc_dist(ti->hit, cy.pos) * calc_dist(ti->hit, cy.pos) - cy.radius * cy.radius)));
	printf("%f \n", z);
	// if ((calc_dist(ti->hit, cy.pos) * calc_dist(ti->hit, cy.pos) - cy.radius * cy.radius) < 0)
	// 	printf("YOLO\n");
	norm = vectoradd(cy.pos, vectorscale(z, cy.norm));
	// ti->n = vectorscale(-1, vectorsub(ti->hit, norm));
	ti->mat = cy.mat;
	normalize_vec(&ti->n);
	ti->n = (vectordot(r->dir, ti->n) > EPSILON) ? vectorscale(-1, ti->n) : ti->n;
	
	// printf("%f %f %f \n", ti->n.x, ti->n.y, ti->n.z);
	ti->match = true;
	// printf("T0T1 %f %f %f \n", t0, t1, ti->t);
	// if (t0 > t1)
	// 	ft_swap(&t0, &t1);
	// ti->t = t0;
	// intersect_circles(t2, ti, r, &cy);
	// if (t2[0] < t0 && t2[0] < t1)
	// {
	// 	t0 = t2[0];
	// 	cy.fov = 1;
	// }
	// if (t2[1] < t0 && t2[1] < t1)
	// {
	// 	t1 = t2[1];
	// 	cy.fov = 1;
	// }
	// ti->t = (t0 < t1) ? t0 : t1;
	//if (ti->t < EPSILON)
	//	return(invalid_ti(ti));
	// nearest intersection
	// if (t0 < EPSILON)
	// {
	// 	ti->match = false;
	// 	return (*ti);
	// }
	return (*ti);
}

t_inter
	intersect_r_cy(t_stuff *st, void *ptr, t_inter *ti, ray *r)
{
	t_cy	cy;
	vec		p0;
	double  t0, t1;
	vec 	norm;
	int k[4];
	double t2[2];

	cy = *(t_cy *)ptr;
	ti->match = true;
	normalize_vec(&cy.norm);
	n_vec(r->start.x - cy.pos.x, r->start.y- cy.pos.y, r->start.z  - cy.pos.z, &p0);
	cy.top = vectoradd(cy.pos, vectorscale(cy.len, cy.norm));
	//double a = r->dir.x * r->dir.x + r->dir.z * r->dir.z;
	//double b = 2 * (r->dir.x * p0.x +r->dir.z * p0.z);
	//double c = p0.x * p0.x + p0.z * p0.z - cy.radius * cy.radius;

	// double a = r->dir.x * r->dir.x + r->dir.z * r->dir.z;
	// double b = 2 * r->start.x * r->dir.x + 2 * r->start.z * r->dir.z;
	// double c = r->start.x * r->start.x + r->start.z * r->start.z - cy.radius * cy.radius;
	// double delta = b * b - (a * c) * 4;

	vec hit1 = vectorsub(r->start, cy.pos); // o2
	cy.norm = normalize_v(cy.norm);  // o1
	vec hit2 = vectorsub(hit1, vectorscale(vectordot(hit1, cy.norm), cy.norm)); // o4
	vec norm1 = vectorsub(cy.top, cy.pos);
	vec hit3 = vectorsub(r->dir, vectorscale(vectordot(r->dir, cy.norm), cy.norm));
	double a = vectordot(hit3, hit3);
	double b = 2 * vectordot(hit3, hit2);
	double c = vectordot(hit2, hit2) - cy.radius * cy.radius;
	k[0] = b * b - 4 * a * c;

	// delta < 0 means no intersections
	if (k[0] < EPSILON)
		return(invalid_ti(ti));
	t0 = (-b + sqrt(k[0])) / (2 * a);
	t1 = (-b - sqrt(k[0])) / (2 * a);	
	vec in = vectorsub(vectoradd(r->start, vectorscale(t0, r->dir)), cy.pos);
	vec out = vectorsub(vectoradd(r->start, vectorscale(t1, r->dir)), cy.pos);
	if ((vectordot(in, norm1) > vectordot(norm1, norm1) || vectordot(in, norm1) < 0) &&
			(vectordot(out, norm1) > vectordot(norm1, norm1) || vectordot(out, norm1) < 0))
		return(invalid_ti(ti));
	// if (t0 > t1)
	// 	ft_swap(&t0, &t1);
	// ti->t = t0;
	////intersect_circles(t2, r, &cy);
	////if (t2[0] < t0 && t2[0] < t1)
	////{
	////	t0 = t2[0];
	////	cy.fov = 1;
	////}
	////if (t2[1] < t0 && t2[1] < t1)
	////{
	////	t1 = t2[1];
	////	cy.fov = 1;
	////}
	ti->t = (t0 < t1) ? t0 : t1;
	if (ti->t < EPSILON)
		return(invalid_ti(ti));
	// nearest intersection
	// if (t0 < EPSILON)
	// {
	// 	ti->match = false;
	// 	return (*ti);
	// }	

	double y0 = r->start.y + (t0 * r->dir.y);
	double y1 = r->start.y + (t1 * r->dir.y);
	ti->mat = cy.mat;
	//printf("%f \n", y);
	// if (y0 < -1)
	// {
	// 	if (y1 < cy.pos.y)
	// 		return(invalid_ti(ti));
	// 	else
	// 	{
	// 		// hit the cap
	// 		double th = t0 + (t1 - t0) * (y0 + 1) / (y0 - y1);
	// 		if (th <= EPSILON)
	// 			return(invalid_ti(ti));
	// 		ti->hit = vectoradd(r->start, vectorscale(th, r->dir));
	// 		n_vec(0, -1, 0, &norm);
	// 		ti->n = norm;
	// 		normalize_vec(&ti->n);
	// 		ti->match = true;
	// 		return (*ti);
	// 	}
	// }
	// if (y0 >= cy.pos.y && y0 <= cy.top.y)
	// {
		// hit the cylinder bit
		// if (t0 <= EPSILON)
		// 	return(invalid_ti(ti));
		// ti->hit =  vectoradd(r->start, vectorscale(t0, r->dir));
		ti->mat = cy.mat;
		ti->hit =  vectoradd(r->start, vectorscale(ti->t, r->dir));
		double z = sqrt(fabs((calc_dist(ti->hit, cy.pos) * calc_dist(ti->hit, cy.pos) - cy.radius * cy.radius)));
		// printf("%f \n", z);
		// if ((calc_dist(ti->hit, cy.pos) * calc_dist(ti->hit, cy.pos) - cy.radius * cy.radius) < 0)
		// 	printf("YOLO\n");
		norm = vectoradd(cy.pos, vectorscale(z, cy.norm));
		ti->n = vectorsub(ti->hit, norm);
		normalize_vec(&ti->n);
		ti->n = (vectordot(r->dir, ti->n) > 0) ? vectorscale(-1, ti->n) : ti->n;
		ti->match = true;
		return (*ti);
	// }
	// else if (y0 > cy.top.y)
	// {
	// 	if (y1 > cy.top.y)
	// 		return(invalid_ti(ti));
	// 	else
	// 	{
	// 		// hit the cap
	// 		double th = t0 + (t1 - t0) * (y0 - 1) / (y0 - y1);
	// 		if (th <= EPSILON)
	// 			return(invalid_ti(ti));
	// 		ti->hit = vectoradd(r->start, vectorscale(th, r->dir));
	// 		n_vec(0, 1, 0, &norm);
	// 		ti->n = norm;
	// 		normalize_vec(&ti->n);
	// 		ti->match = true;
	// 		return (*ti);
	// 	}
	// }
	ti->match = false;
	return (*ti);
}


t_inter
	intersect_r_cy(t_stuff *st, void *ptr, t_inter *ti, ray *r)
{
	t_cy	cy;
	vec		p0;
	double  t0, t1;
	vec 	norm;

	cy = *(t_cy *)ptr;
	ti->match = false;
	normalize_vec(&cy.norm);
	n_vec(r->start.x - cy.pos.x, r->start.y- cy.pos.y, r->start.z  - cy.pos.z, &p0);
	
	//double a = r->dir.x * r->dir.x + r->dir.z * r->dir.z;
	//double b = 2 * (r->dir.x * p0.x +r->dir.z * p0.z);
	//double c = p0.x * p0.x + p0.z * p0.z - cy.radius * cy.radius;

	double a = r->dir.x * r->dir.x + r->dir.z * r->dir.z;
	double b = 2 * r->start.x * r->dir.x + 2 * r->start.z * r->dir.z;
	double c = r->start.x * r->start.x + r->start.z * r->start.z - cy.radius * cy.radius;

	double delta = b * b - (a * c) * 4;

	//use EPSILON because of computation errors between doubles

	// delta < 0 means no intersections
	if (delta < EPSILON)
	{
		ti->match = false;
		return (*ti);
	}
	t0 = (-b + sqrt(delta)) / (2 * a);
	t1 = (-b - sqrt(delta)) / (2 * a);	
	if (t0 > t1)
		ft_swap(&t0, &t1);
	ti->t = t0;
	// nearest intersection
	// if (t0 < EPSILON)
	// {
	// 	ti->match = false;
	// 	return (*ti);
	// }	
	double y0 = r->start.y + (t0 * r->dir.y);
	double y1 = r->start.y + (t1 * r->dir.y);
	ti->mat = cy.mat;
	//printf("%f \n", y);
	if (y0 < -1)
	{
		if (y1 < -1)
		{
			ti->match = false;
			return (*ti);
		}
		else
		{
			// hit the cap
			double th = t0 + (t1 - t0) * (y0 + 1) / (y0 - y1);
			if (th <= EPSILON)
			{
				ti->match = false;
				return (*ti);
			}
		
			ti->hit = vectoradd(r->start, vectorscale(th, r->dir));
			n_vec(0, -1, 0, &norm);
			ti->n = norm;
			normalize_vec(&norm);
			ti->match = true;
			return (*ti);
		}
	}
	else if (y0 >= -1 && y0 <= 1)
	{
		// hit the cylinder bit
		if (t0 <= 0)
		{
			ti->match = false;
			return (*ti);
		}
			
		ti->hit =  vectoradd(r->start, vectorscale(t0, r->dir));
		n_vec(ti->hit.y, 0, ti->hit.z, &norm);
		ti->n = norm;
		normalize_vec(&norm);
		ti->match = true;
		return (*ti);
	}
	else if (y0 > 1)
	{
		if (y1 > 1)
		{
			ti->match = false;
			return (*ti);
		}
		else
		{
			// hit the cap
			double th = t0 + (t1 - t0) * (y0 - 1) / (y0 - y1);
			if (th <= EPSILON)
			{
				ti->match = false;
				return (*ti);
			}
			ti->hit = vectoradd(r->start, vectorscale(th, r->dir));
			n_vec(0, 1, 0, &norm);
			ti->n = norm;
			normalize_vec(&norm);
			ti->match = true;
			return (*ti);
		}
	}
	ti->match = false;
	return (*ti);
}