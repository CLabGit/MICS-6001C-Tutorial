from fir_interpolate_asym import *
from aie_common import *
import fir_polyphase_decomposer as poly
from vmc_fir_utils import *

#### VMC validators ####
def vmc_validate_coeff_type(args):
    data_type = args["data_type"]
    coef_type = args["coef_type"]
    AIE_VARIANT = args["AIE_VARIANT"]
    standard_checks =  fn_validate_coeff_type(data_type, coef_type)
    type_check = fn_type_support(data_type, coef_type, AIE_VARIANT)
    for check in (standard_checks,type_check) :
        if check["is_valid"] == False :
            return check
    return {"is_valid": True}


def vmc_validate_input_window_size(args):
    input_window_size = args["input_window_size"]
    data_type = args["data_type"]
    use_coeff_reload = args["use_coeff_reload"]
    coef_type = args["coef_type"]
    coeff = args["coeff"]
    interpolate_factor = args["interpolate_factor"]
    api = 1
    ssr = args["ssr"]
    fir_length = fn_get_fir_length(args)
    return fn_validate_input_window_size(data_type, coef_type, fir_length, interpolate_factor, input_window_size, api, ssr)

def vmc_validate_casc_length(args):
    casc_length = args["casc_length"]
    return fn_validate_casc_len(casc_length);

def validate_sat_mode(args):
    sat_mode = args["sat_mode"]
    return fn_validate_satMode(sat_mode);


def vmc_validate_coeff(args):
    use_coeff_reload = args["use_coeff_reload"]
    coef_type = args["coef_type"]
    coeff = args["coeff"]
    data_type = args["data_type"]
    casc_length = args["casc_length"]
    interpolate_factor = args["interpolate_factor"]
    ssr = args["ssr"]
    AIE_VARIANT = args["AIE_VARIANT"]
    api = 1
    AIE_VARIANT = args["AIE_VARIANT"]
    dual_ip = args["dual_ip"]
    fir_length = fn_get_fir_length(args)
    return fn_validate_fir_len(data_type, coef_type, fir_length, interpolate_factor, casc_length, ssr, api, use_coeff_reload, dual_ip, AIE_VARIANT)

def vmc_validate_shift_val(args):
    data_type = args["data_type"]
    shift_val = args["shift_val"]
    return fn_validate_shift(data_type, shift_val)

def vmc_validate_ssr(args):
    interpolate_factor = args["interpolate_factor"]
    interp_poly = args["interp_poly"]
    ssr = args["ssr"]
    api = 1
    AIE_VARIANT = args["AIE_VARIANT"]
    return fn_validate_interp_ssr(ssr, interpolate_factor, interp_poly, api, AIE_VARIANT)

def vmc_validate_interp_poly(args):
  interp_poly = args["interp_poly"]
  ipol_factor = args["interpolate_factor"]
  return fn_validate_para_interp_poly(ipol_factor, interp_poly)

def vmc_validate_interpolate_factor(args):
    interpolate_factor = args["interpolate_factor"]
    AIE_VARIANT = args["AIE_VARIANT"]
    return fn_validate_interpolate_factor(interpolate_factor, AIE_VARIANT)

def vmc_validate_input_ports(args):
    dual_ip = args["dual_ip"]
    num_outputs = fn_get_num_outputs(args)
    AIE_VARIANT = args["AIE_VARIANT"]
    api = 1
    return fn_validate_interp_dual_ip(num_outputs,api, dual_ip, AIE_VARIANT)

def vmc_validate_out_ports(args):
    num_outputs = fn_get_num_outputs(args)
    AIE_VARIANT = args["AIE_VARIANT"]
    api = 1
    return fn_validate_num_outputs(api, num_outputs, AIE_VARIANT)

def vmc_validate_rnd_mode(args):
    rnd_mode = args["rnd_mode"]
    AIE_VARIANT = args["AIE_VARIANT"]
    return fn_validate_roundMode(rnd_mode, AIE_VARIANT)

#### VMC graph generator ####
def vmc_generate_graph(name, args):
    tmpargs = {}
    tmpargs["TT_DATA"] = args["data_type"]
    use_coeff_reload = args["use_coeff_reload"]
    coef_type = args["coef_type"]
    coeff = args["coeff"]
    tmpargs["TT_COEFF"] = coef_type
    tmpargs["TP_FIR_LEN"] = fn_get_fir_length(args)
    tmpargs["TP_SHIFT"] = args["shift_val"]
    tmpargs["TP_RND"] = args["rnd_mode"]
    tmpargs["TP_INPUT_WINDOW_VSIZE"] = args["input_window_size"]
    tmpargs["TP_INTERPOLATE_FACTOR"] = args["interpolate_factor"]
    casc_length = args["casc_length"]
    tmpargs["TP_CASC_LEN"] = casc_length
    tmpargs["TP_USE_COEFF_RELOAD"] = 1 if args["use_coeff_reload"] else 0
    tmpargs["TP_NUM_OUTPUTS"] = fn_get_num_outputs(args)
    tmpargs["TP_DUAL_IP"] = 1 if args["dual_ip"] else 0
    tmpargs["TP_API"] = 1
    tmpargs["TP_SSR"] = args["ssr"]
    tmpargs["coeff"] = args["coeff"]
    tmpargs["TP_PARA_INTERP_POLY"] = args["interp_poly"]
    tmpargs["TP_SAT"] = args["sat_mode"]

    return generate_graph(name, tmpargs)
