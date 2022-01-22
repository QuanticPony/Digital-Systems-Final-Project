/*
 * Collisions.cpp
 *
 *  Created on: 7 ene 2022
 *      Author: QuanticPony
 */

// The next 3 functions are taken from: https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
bool onSegment(Vector2D p, Vector2D q, Vector2D r)
{
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
       return true;
    return false;
}

int orientation(Vector2D p, Vector2D q, Vector2D r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;

    return (val > 0)? 1: 2;
}

bool doIntersect(Line line1, Line line2)
{
	Vector2D p1 = line1.position;
	Vector2D q1 = line1.position.sume(line1.line);
	Vector2D p2 = line2.position;
	Vector2D q2 = line2.position.sume(line2.line);

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

// End of copied code.


bool Collisions::colliding(Line line1, Line line2)
{
	return doIntersect(line1, line2);
}

bool Collisions::colliding(Particle ball1, Particle ball2)
{
	return ball1.position.subtract(ball2.position).modulus() <= (ball1.radius + ball2.radius);
}

bool Collisions::colliding(Line line1, Particle ball)
{
	Vector2D normal = line1.line.normal().unitary();
	Vector2D diff = ball.position.subtract(line1.midpoint());
	if (diff.modulus() < line1.line.modulus()/2+ball.radius){
		return abs(normal.dot(diff)) < ball.radius;
	}
	return false;
}


void Collisions::resolveCollision(Line &line1, Line &line2)
{
	// TODO: this doesnt work. But i'm not in the mood
	if ((!line1.moveable) && (!line2.moveable)){
		return;
	}
	float inv_M = 1 / (1 / line1.inv_mass + 1 / line2.inv_mass);

	Vector2D dV = line1.velocity.subtract(line2.velocity);
	Vector2D dX = line1.line.normal().unitary();

	float dot = dV.dot(dX);

	if (line1.moveable)
		line1.velocity.add(dX.multiply(-2 * inv_M / line2.inv_mass * dot));
	
	if (line2.moveable){
		dX = line2.line.normal().unitary();
		dV.scale(-1);
		dot = dV.dot(dX);
		line2.velocity.add(dX.multiply(-2 * inv_M / line1.inv_mass * dot));
	}
}



bool Collisions::colliding(Block block, Particle ball)
{
	return (block.position.subtract(ball.position).modulus() < ball.radius + block.radius);
}

void Collisions::resolveCollision(Particle &ball1, Particle &ball2)
{
	if ((!ball1.moveable) && (!ball2.moveable)){
		return;
	}
	float inv_M = 1 / (1 / ball1.inv_mass + 1 / ball2.inv_mass);

	Vector2D dV = ball1.velocity.subtract(ball2.velocity);
	Vector2D dX = ball1.position.subtract(ball2.position);
	float dX_m = dX.modulus();

	float dot = dV.dot(dX);
	if (dot >= 0)
	{
		return;
	}

	if (ball1.moveable)
		ball1.velocity.add(dX.multiply(-2 * inv_M / ball2.inv_mass * dot / dX_m / dX_m));
	
	if (ball2.moveable){
		dX.scale(-1);
		dV.scale(-1);
		ball2.velocity.add(dX.multiply(-2 * inv_M / ball1.inv_mass * dot / dX_m / dX_m));
	}
}

void Collisions::resolveCollision(Block &block, Particle &ball)
{
	if ((!ball.moveable) && (!block.moveable)){
		return;
	}
	for (int B = 0; B < 4; B++)
	{
		if(Collisions::colliding(block.sides[B], ball)){
			block.sides[B].velocity = block.velocity;
			block.sides[B].inv_mass = block.inv_mass;
			block.sides[B].moveable = block.moveable;
			Collisions::resolveCollision(block.sides[B], ball);
			block.velocity = block.sides[B].velocity;
			break;
		}
	}
}

void Collisions::resolveCollision(Line &line, Particle &ball)
{
	if ((!ball.moveable) && (!line.moveable)){
		return;
	}

	float inv_M = 0;
	if (ball.moveable){
		inv_M += 1/ball.inv_mass;
	}
	
	if (line.moveable){
		inv_M += 1/line.inv_mass;
	}
	inv_M = 1/inv_M;


	Vector2D dV = ball.velocity.subtract(line.velocity);
	Vector2D dX;
	
	Vector2D candidate;
	bool done = false;

	candidate = ball.position.subtract(line.position);
	if (candidate.modulus() < 0.8*ball.radius) {
		dX = candidate.unitary().multiply(-1);
		done = true;
	}

	candidate = ball.position.subtract(line.position.sume(line.line));
	if (candidate.modulus() < 0.8*ball.radius && !done) {
		dX = candidate.unitary().multiply(-1);
		done = true;
	}

	if (!done) {
		dX = line.line.normal().unitary();
	}

	float dot = dV.dot(dX);

	float mass_term;
	if (ball.moveable){
		mass_term = line.moveable? inv_M / line.inv_mass : 1;
		ball.velocity.add(dX.multiply(-2 * mass_term * dot));
	}
	dX.scale(-1);
	if (line.moveable){
		mass_term = ball.moveable? inv_M / ball.inv_mass : 1;
		line.velocity.add(dX.multiply(-2 * mass_term * dot));
	}
}


bool Collisions::colliding(Line line, Block block)
{
	return ((line.position.subtract(block.position).modulus()) < (line.line.modulus()/2 + block.radius));
}

void Collisions::resolveCollision(Line &line, Block &block)
{
	if ((!line.moveable) && (!block.moveable)){
		return;
	}
	for (int B = 0; B < 4; B++)
	{
		if(Collisions::colliding(block.sides[B], line)){
			block.sides[B].velocity = block.velocity;
			block.sides[B].inv_mass = block.inv_mass;
			block.sides[B].moveable = block.moveable;
			Collisions::resolveCollision(block.sides[B], line);
			block.velocity = block.sides[B].velocity;
			break;
		}
	}
}