#include "effect_test.h"

bool EffectTest::init()
{
	LPDIRECT3DDEVICE9 p_d3d_device = ge::GEEngine::get_device();
	if(p_d3d_device == NULL) return false;

	create_from_file("./shader/diffuse.fx");
	if(p_fx_ == NULL) return false;

	D3DXHANDLE h_tech_main = p_fx_->GetTechniqueByName("TechMain");
	p_fx_->SetTechnique(h_tech_main);

	D3DXHANDLE h_ambient_mtrl		= p_fx_->GetParameterByName(0, "AmbientMtrl");
	D3DXHANDLE h_diffuse_mtrl		= p_fx_->GetParameterByName(0, "DiffuseMtrl");
	D3DXHANDLE h_light_direction	= p_fx_->GetParameterByName(0, "LightDirection");

	D3DXVECTOR4 directionToLight(-0.57f, 0.57f, -0.57f, 0.0f);
	p_fx_->SetVector(h_light_direction, &directionToLight);

	D3DXVECTOR4 ambientMtrl(0.0f, 0.0f, 1.0f, 1.0f);
	D3DXVECTOR4 diffuseMtrl(0.0f, 0.0f, 1.0f, 1.0f);
	p_fx_->SetVector(h_ambient_mtrl, &ambientMtrl);
	p_fx_->SetVector(h_diffuse_mtrl, &diffuseMtrl);
	return true;
}

void EffectTest::render( ge::GEObject* obj, time_t time_elapsed )
{
	LPDIRECT3DDEVICE9 p_d3d_device = ge::GEEngine::get_device();
	if (p_d3d_device == NULL) return;
	ge::GERender* p_render = ge::GEEngine::get_instance()->get_render();
	if (p_render == NULL) return;
	if (p_fx_ == NULL) return;

	D3DXHANDLE h_wvm = p_fx_->GetParameterByName(0, "gWV");
	D3DXHANDLE h_wvpm = p_fx_->GetParameterByName(0, "gWVP");

	D3DXMATRIX view_matrix = obj->get_world_matrix();
	view_matrix = view_matrix * p_render->get_view_matrix();
	D3DXMATRIX view_proj_matrix = obj->get_world_matrix();
	view_proj_matrix = view_proj_matrix * p_render->get_view_matrix() * p_render->get_proj_matrix();

	p_fx_->SetMatrix(h_wvm, &view_matrix);
	p_fx_->SetMatrix(h_wvpm, &view_proj_matrix);
	p_fx_->CommitChanges();

	ge::GEREffect::render(obj, time_elapsed);
}
