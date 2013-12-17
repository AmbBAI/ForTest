#include "scene_test.h"

SceneTest::SceneTest()
:p_test_model_(NULL),
p_fps_text_(NULL),
fps_font_id_(-1)
{
}

bool SceneTest::init_fps_text()
{
	p_fps_text_ = new ge::GEOText();
	if (p_fps_text_ == NULL) return false;

	ge::GE_FONT ge_font = {"consolas", 16, DEFAULT_CHARSET, 0, false };
	ge::GEEngine* p_engine = ge::GEEngine::get_instance();
	if (p_engine == NULL) return false;
	ge::GERFontManager* p_font_manager = p_engine->get_font_manager();
	if (p_font_manager == NULL) return false;

	fps_font_id_ = p_font_manager->add_d3dx_font(ge_font);
	ge::GE_TEXT_STYLE style = {
		fps_font_id_,
		DT_LEFT | DT_TOP,
		RGBA(0xff, 0xff, 0xff, 0xff),
		false, 0, RGBA(0xff, 0xff, 0xff, 0xff),
		false, 0, RGBA(0xff, 0xff, 0xff, 0xff)
	};
	p_fps_text_->set_text_style(style);

	ge::GE_IRECT rect(0, 0, 100, 20);
	p_fps_text_->set_rect(rect);

	object_map_[0] = p_fps_text_;
	return true;
}

bool SceneTest::init_test_model()
{
	p_test_model_ = new ModelTest();
	if (p_test_model_ == NULL) return false;

	ge::GE_VERTEX vertex_buff[8];
	vertex_buff[0] = ge::GE_VERTEX(-1.0f, -1.0f, -1.0f);
	vertex_buff[1] = ge::GE_VERTEX(-1.0f, 1.0f, -1.0f);
	vertex_buff[2] = ge::GE_VERTEX( 1.0f, 1.0f, -1.0f);
	vertex_buff[3] = ge::GE_VERTEX( 1.0f, -1.0f, -1.0f);
	vertex_buff[4] = ge::GE_VERTEX(-1.0f, -1.0f, 1.0f);
	vertex_buff[5] = ge::GE_VERTEX(-1.0f, 1.0f, 1.0f);
	vertex_buff[6] = ge::GE_VERTEX( 1.0f, 1.0f, 1.0f);
	vertex_buff[7] = ge::GE_VERTEX( 1.0f, -1.0f, 1.0f);
	p_test_model_->set_vertices(vertex_buff, 8);

	WORD index_buff[36];
	index_buff[0] = 0; index_buff[1] = 1; index_buff[2] = 2;
	index_buff[3] = 0; index_buff[4] = 2; index_buff[5] = 3;
	index_buff[6] = 4; index_buff[7] = 6; index_buff[8] = 5;
	index_buff[9] = 4; index_buff[10] = 7; index_buff[11] = 6;
	index_buff[12] = 4; index_buff[13] = 5; index_buff[14] = 1;
	index_buff[15] = 4; index_buff[16] = 1; index_buff[17] = 0;
	index_buff[18] = 3; index_buff[19] = 2; index_buff[20] = 6;
	index_buff[21] = 3; index_buff[22] = 6; index_buff[23] = 7;
	index_buff[24] = 1; index_buff[25] = 5; index_buff[26] = 6;
	index_buff[27] = 1; index_buff[28] = 6; index_buff[29] = 2;
	index_buff[30] = 4; index_buff[31] = 0; index_buff[32] = 3;
	index_buff[33] = 4; index_buff[34] = 3; index_buff[35] = 7;
	p_test_model_->set_indices(index_buff, 36);

	object_map_[1] = p_test_model_;
	return true;
}

bool SceneTest::show()
{
	init_fps_text();
	init_test_model();
	return true;
}


bool SceneTest::hide()
{
	p_fps_text_->destory();
	delete p_test_model_;
	p_test_model_ = NULL;

	p_test_model_->destory();
	delete p_test_model_;
	p_test_model_ = NULL;

	object_map_.clear();
	return true;
}

void SceneTest::update( time_t time_elapsed )
{
	if(NULL != p_fps_text_)
	{
		float fps = ge::GEApp::get_instance()->get_fps();
		char buff[32];
		sprintf_s(buff, "fps %.2f", fps);
		p_fps_text_->set_text(buff);
	}

	ge::GEScene::update(time_elapsed);
}