#include "cli.h"
#include "temperature.h"
#include "storage.h"

static void get_temperature(void);
static void get_count(void);
static void Help(void);

commandStruct_t commands[] = {
    {"temperature", get_temperature, "Shows temperature value"},
    {"count", get_count, "Shows storage data count"},
    {"help", Help, "List all commands"},
};

#define COMMAND_COUNT           (sizeof(commands) / sizeof(commands[0]))
#define CLI_BUFFER_SIZE         64

static char inputBuffer[CLI_BUFFER_SIZE];
static int idx = 0;

void ProcessCommands(uint8_t c)
{

    // Simple command reading loop
    if (c == '\r')
    {
        // do nothing
    }else if(c == '\n')
    { // End of command
        inputBuffer[idx] = '\0'; // Null-terminate string

        // Match command
        for (int i = 0; i < COMMAND_COUNT; i++)
        {
            if (strcmp(inputBuffer, commands[i].name) == 0)
            {
                commands[i].execute(); // Execute the command
                break;
            }
        }
        idx = 0; // Reset index for next command
    } else if (idx < CLI_BUFFER_SIZE)
    {
        inputBuffer[idx++] = (char)c; // Store character
    }
}

static void get_temperature(void)
{
    uint16_t temperature_value = temperature_get();
    printf("Temperatura: %d.%d C\n", temperature_value/10, temperature_value%10);
}

static void get_count(void)
{
    uint8_t count_data = storage_getCount();
    printf("Count: %d\n", count_data);
}


static void Help(void)
{
	printf("===================================\n");
    for (int i = 0; i < COMMAND_COUNT; i++) {
    	printf("%s: %s\n", commands[i].name, commands[i].help);
    }
    printf("===================================\n");
}