#pragma once
#include "Hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public Hittable
{
public:
	hittable_list() {}
	hittable_list(shared_ptr<Hittable> object) { add(object); }

	void clear() { objects.clear(); }
	void add(shared_ptr<Hittable> object) { objects.push_back(object); }

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	std::vector<shared_ptr<Hittable>> objects;
};