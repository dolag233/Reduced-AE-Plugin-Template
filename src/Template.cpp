#include "Template.h"

static PF_Err
About(
	PF_InData* in_data,
	PF_OutData* out_data,
	PF_ParamDef* params[],
	PF_LayerDef* output)
{
	if (!suitesP)
	{
		static auto suites = AEGP_SuiteHandler(in_data->pica_basicP);
		suitesP = &suites;
	}

	suitesP->ANSICallbacksSuite1()->sprintf(out_data->return_msg,
	                                        "%s v%d.%d\r%s",
	                                        "This is a pure and tiny template for AE effect.",
	                                        MAJOR_VERSION,
	                                        MINOR_VERSION,
	                                        "Template");
	return PF_Err_NONE;
}

static PF_Err
GlobalSetup(
	PF_InData* in_data,
	PF_OutData* out_data,
	PF_ParamDef* params[],
	PF_LayerDef* output)
{
	out_data->my_version = PF_VERSION(MAJOR_VERSION,
	                                  MINOR_VERSION,
	                                  BUG_VERSION,
	                                  STAGE_VERSION,
	                                  BUILD_VERSION);

	out_data->out_flags = PF_OutFlag_DEEP_COLOR_AWARE; // just 16bpc, not 32bpc
	out_data->out_flags2 = PF_OutFlag2_SUPPORTS_THREADED_RENDERING; // support MFR

	// all suites are suggested to be obtained in the main thread, like GlobalSetup
	if (!suitesP)
	{
		static auto suites = AEGP_SuiteHandler(in_data->pica_basicP);
		suitesP = &suites;
	}

	return PF_Err_NONE;
}

static PF_Err
ParamsSetup(
	PF_InData* in_data,
	PF_OutData* out_data,
	PF_ParamDef* params[],
	PF_LayerDef* output)
{
	out_data->num_params = 1;

	return PF_Err_NONE;
}

static PF_Err
Render(
	PF_InData* in_data,
	PF_OutData* out_data,
	PF_ParamDef* params[],
	PF_LayerDef* output)
{
	PF_Err err = PF_Err_NONE;

	// just copy the input data
	ERR(in_data->utils->copy(0, &(params[0]->u.ld), output, &(in_data->extent_hint), &(output->extent_hint)));

	return err;
}

PF_Err
EffectMain(
	PF_Cmd cmd,
	PF_InData* in_data,
	PF_OutData* out_data,
	PF_ParamDef* params[],
	PF_LayerDef* output,
	void* extra)
{
	PF_Err err = PF_Err_NONE;

	try
	{
		switch (cmd)
		{
		case PF_Cmd_ABOUT:

			err = About(in_data,
			            out_data,
			            params,
			            output);
			break;

		case PF_Cmd_GLOBAL_SETUP:

			err = GlobalSetup(in_data,
			                  out_data,
			                  params,
			                  output);
			break;

		case PF_Cmd_PARAMS_SETUP:

			err = ParamsSetup(in_data,
			                  out_data,
			                  params,
			                  output);
			break;

		case PF_Cmd_RENDER:

			err = Render(in_data,
			             out_data,
			             params,
			             output);
			break;
		}
	}
	catch (PF_Err& thrown_err)
	{
		err = thrown_err;
	}

	return err;
}
