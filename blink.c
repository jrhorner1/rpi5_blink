#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CHIP_PATH "/dev/gpiochip4"
#define PIN   21

int main(void) {
    struct gpiod_chip *chip;
    struct gpiod_line_settings *settings;
    struct gpiod_line_request *request = NULL;
    struct gpiod_line_config *line_conf;
    struct gpiod_request_config *req_conf = NULL;
    static const unsigned int offset = PIN;

    printf("Libgpiod version %s\n", gpiod_api_version());\

    // open the chip
    chip = gpiod_chip_open(CHIP_PATH);
    if (!chip)
    {
        printf("Failed to open chip");
        return EXIT_FAILURE;
    }

    // create new line settings
    settings = gpiod_line_settings_new();
    if (!settings)
        goto close_chip;

    // set the GPIO direction as an output
    gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);
    // set the initial output value
    gpiod_line_settings_set_output_value(settings, GPIOD_LINE_VALUE_ACTIVE);

    // create a new line config
    line_conf = gpiod_line_config_new();
    if (!line_conf)
        goto free_settings;

    // add the line settings to the line config
    int ret = gpiod_line_config_add_line_settings(line_conf, &offset, 1, settings);
    if (ret)
        goto free_line_conf;

    // create a new request config 
    req_conf = gpiod_request_config_new();
    if (!req_conf)
        goto free_line_conf;

    // set the consumer to the program name
    gpiod_request_config_set_consumer(req_conf, "blink");

    // make the request using the chip, request config, and line config
    request = gpiod_chip_request_lines(chip, req_conf, line_conf);

    // clear out the request config
    gpiod_request_config_free(req_conf);

free_line_conf:
    // clear out the line config
    gpiod_line_config_free(line_conf);

free_settings:
    // clear out the line settings
    gpiod_line_settings_free(settings);

close_chip:
    // close the chip
    gpiod_chip_close(chip);

    if (!request) {
        printf("failed to request line\n");
        return EXIT_FAILURE;
    }

    // blink the led ten times
    for (int i = 0; i < 10; i++) 
    {   // 1 works in place of GPIOD_LINE_VALUE_ACTIVE
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_ACTIVE); sleep(1);
        sleep(1);
        // 0 works in place of GPIOD_LINE_VALUE_INACTIVE
        gpiod_line_request_set_value(request, offset, GPIOD_LINE_VALUE_INACTIVE); sleep(1);
        sleep(1);
    }

    // release the GPIO request
    gpiod_line_request_release(request);

    return EXIT_SUCCESS;
}