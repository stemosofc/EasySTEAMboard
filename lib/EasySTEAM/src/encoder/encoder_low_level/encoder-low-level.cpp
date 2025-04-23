#include "encoder-low-level.hpp"


static const char * TAG = "Encoder";

EncoderLL::EncoderLL()
{

}

EncoderLL::~EncoderLL()
{
    pcnt_del_unit(enc_unit_handler);
    pcnt_del_channel(enc_channel_A_handler);
    pcnt_del_channel(enc_channel_B_handler);
}

void EncoderLL::initialize(gpio_num_t pinA, gpio_num_t pinB)
{
    aPinNumber = pinA;
    bPinNumber = pinB;

    gpio_pad_select_gpio(aPinNumber);
    gpio_pad_select_gpio(bPinNumber);

    esp_err_t direction_result = gpio_set_direction(aPinNumber, GPIO_MODE_INPUT);
    direction_result |= gpio_set_direction(bPinNumber, GPIO_MODE_INPUT);

    if(direction_result)
        log_e( "Failed to set pins[A, B](%d, %d) to INPUT MODE", aPinNumber, bPinNumber);

    esp_err_t pulldown_result = gpio_pulldown_en(aPinNumber);
    pulldown_result |= gpio_pulldown_en(bPinNumber);

    if(pulldown_result)
        log_e( "Failed to set pins[A, B](%d, %d) to PULLDOWN MODE", aPinNumber, bPinNumber);

    enc_unit_config.high_limit = UPPER_LIMIT;
    enc_unit_config.low_limit = LOWER_LIMIT;
    enc_unit_config.flags.accum_count = ACCUM;

    esp_err_t unit_result = pcnt_new_unit(&enc_unit_config, &enc_unit_handler);

    if(unit_result)
        log_e( "Failed to set pins[A, B](%d, %d) on Encoder with code: %s", aPinNumber, bPinNumber, esp_err_to_name(unit_result));

    enc_channel_A_config.edge_gpio_num = aPinNumber;
    enc_channel_A_config.level_gpio_num = bPinNumber;

    esp_err_t channelA_result = pcnt_new_channel(enc_unit_handler, &enc_channel_A_config, &enc_channel_A_handler);

    if(channelA_result)
        log_e( "Failed to create channel A with code: %s", esp_err_to_name(channelA_result));

    enc_channel_B_config.edge_gpio_num = bPinNumber;
    enc_channel_B_config.level_gpio_num = aPinNumber;

    esp_err_t channelB_result = pcnt_new_channel(enc_unit_handler, &enc_channel_B_config, &enc_channel_B_handler);

    if(channelB_result)
        log_e( "Failed to create channel B with code: %s", esp_err_to_name(channelB_result));

    esp_err_t channelA_cfg_result = pcnt_channel_set_edge_action(enc_channel_A_handler, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE);
    channelA_cfg_result |= pcnt_channel_set_level_action(enc_channel_A_handler, PCNT_CHANNEL_LEVEL_ACTION_INVERSE, PCNT_CHANNEL_LEVEL_ACTION_KEEP);

    if(channelA_cfg_result)
        log_e( "Failed to configure channel A");

    esp_err_t channelB_cfg_result = pcnt_channel_set_edge_action(enc_channel_B_handler, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE);
    channelB_cfg_result |= pcnt_channel_set_level_action(enc_channel_B_handler, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE);

    if(channelB_cfg_result)
        log_e( "Failed to configure channel B");

    setFilterInNanoseconds(DEFAULT_NS_FILTER);

    enable();

    reset();

    start();
}

void EncoderLL::setFilterInNanoseconds(uint32_t nanoseconds)
{
    pcnt_glitch_filter_config_t filter_config = {.max_glitch_ns = nanoseconds,};
    esp_err_t filter_result = ESP_OK;
    if(nanoseconds != 0)
        filter_result |= pcnt_unit_set_glitch_filter(enc_unit_handler, &filter_config);
    else
        filter_result |= pcnt_unit_set_glitch_filter(enc_unit_handler, NULL);
    if(filter_result)
        log_e( "Failed to apply filter, code: %s\n", esp_err_to_name(filter_result));
}

int EncoderLL::getCount()
{
    int counts = 0;
    ESP_ERROR_CHECK_WITHOUT_ABORT(pcnt_unit_get_count(enc_unit_handler, &counts));
    return counts;
}

void EncoderLL::reset()
{
    esp_err_t reset_result = pcnt_unit_clear_count(enc_unit_handler);
    if(reset_result)
        log_e( "Failed to clear counts of encoder with code: %s\n", esp_err_to_name(reset_result));
}

void EncoderLL::stop()
{
    esp_err_t stop_result = pcnt_unit_stop(enc_unit_handler);
    if(stop_result)
        log_e( "Failed to stop encoder with code: %s\n", esp_err_to_name(stop_result));
}

void EncoderLL::enable()
{
    esp_err_t enable_result = pcnt_unit_enable(enc_unit_handler);
    if(enable_result)
        log_e( "Failed to enable encoder with code: %s\n", esp_err_to_name(enable_result));
}

void EncoderLL::disable()
{
    esp_err_t disable_result = pcnt_unit_disable(enc_unit_handler);
    if(disable_result)
        log_e( "Failed to disable encoder with code: %s\n", esp_err_to_name(disable_result));
}

void EncoderLL::start()
{
    esp_err_t start_result = pcnt_unit_start(enc_unit_handler);
    if(start_result)
        log_e( "Failed to start encoder with code: %s\n", esp_err_to_name(start_result));
}