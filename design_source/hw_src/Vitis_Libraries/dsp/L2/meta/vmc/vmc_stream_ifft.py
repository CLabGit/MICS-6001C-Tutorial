from vmc_fft_common import *

#### VMC graph generator ####
def vmc_generate_graph(name, args):
    tmpargs = {}
    tmpargs["TT_DATA"] = args["data_type"]
    tmpargs["TT_TWIDDLE"] = args["twiddle_type"]
    tmpargs["TP_POINT_SIZE"] = args["point_size"]
    tmpargs["TP_SHIFT"] = args["shift_val"]
    tmpargs["TP_WINDOW_VSIZE"] = args["input_window_size"]
    #TODO: call to partitioner to determine cascade length
    tmpargs["TP_CASC_LEN"] = args["casc_length"]
    tmpargs["TP_DYN_PT_SIZE"] = 0
    tmpargs["TP_API"] = 1
    ssr = args["ssr"]
    api = 1
    variant = args["AIE_VARIANT"]
    parallel_power = fn_get_parallel_power(ssr, api, variant)

    if parallel_power == -1:
      return isError(f"Invalid SSR value specified. The value should be of the form 2^N between 2 and 512.")

    tmpargs["TP_PARALLEL_POWER"] = parallel_power
    tmpargs["TP_FFT_NIFFT"] = 0
    tmpargs["TP_RND"] = args["rnd_mode"]
    tmpargs["TP_SAT"] = args["sat_mode"]
    tmpargs["AIE_VARIANT"] = args["AIE_VARIANT"]
    tmpargs["TP_USE_WIDGETS"] = 1 if args["use_ssr_widget_kernels"] else 0
    # tmpargs["TP_TWIDDLE_MODE"] = args["TP_TWIDDLE_MODE"]
    tmpargs["TP_TWIDDLE_MODE"] = 0
    return generate_graph(name, tmpargs)
