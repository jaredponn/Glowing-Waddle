#include "geometry.h"

#define APPLY_FUNC_TO_GEOMETRY_VECTORS(func, geometry)                         \
	func(&geometry->verticies);                                            \
	func(&geometry->normals);                                              \
	func(&geometry->colors);                                               \
	func(&geometry->uvs);


void AKY_initGeometry(struct AKY_Geometry *geometry)
{
	APPLY_FUNC_TO_GEOMETRY_VECTORS(Vector_Vec3_t_init, geometry);
}

void AKY_reserveGeometry(struct AKY_Geometry *geometry, size_t memory)
{
	Vector_Vec3_t_reserve(&geometry->verticies, memory);
	Vector_Vec3_t_reserve(&geometry->normals, memory);
	Vector_Vec3_t_reserve(&geometry->colors, memory);
	Vector_Vec3_t_reserve(&geometry->uvs, memory);
}

void AKY_freeGeometry(struct AKY_Geometry *geometry)
{
	APPLY_FUNC_TO_GEOMETRY_VECTORS(Vector_Vec3_t_free, geometry);
}

#undef APPLY_FUNC_TO_GEOMETRY_VECTORS
