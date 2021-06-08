/* 
 * Copyright 2021 seamus@bumblestack.com, Corvideon Limited.
 * Portions of this code were originally created by the OpenNARS authors under the MIT License.

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "app.h"
#include "cJSON.h"

void Process_Args(int argc, char *argv[]) {
    bool inspectionOnExit = false;
    long iterations = -1;
    if (argc >= 4) {
        if (!strcmp(argv[3], "InspectionOnExit")) {
            inspectionOnExit = true;
        }
    }
    if (argc >= 3) {
        if (!strcmp(argv[2], "InspectionOnExit")) {
            inspectionOnExit = true;
        }
    }
    if (argc >= 2) {
        NAR_INIT();
        if (!strcmp(argv[1], "shell")) {
            Shell_Start();
        }
    }
    if (inspectionOnExit) {
        Shell_ProcessInput("*concepts");
        Shell_ProcessInput("*cycling_belief_events");
        Shell_ProcessInput("*cycling_goal_events");
        Shell_ProcessInput("*stats");
    }
}



void systemInit(){
    // set up random number generator
    mysrand(SEED);

    // initialise logging
    setupLogging();
    slog_info("Welcome to BumbleStack!");

    // initialise the bumblestack NARS system
    NAR_INIT();
    slog_info("System initialised.");
    statsPrint(currentTime);
    printAtomTable();
    printConcepts();
    printCyclingBeliefEvents();
    printCyclingGoalEvents();
}


//create a monitor with a list of supported resolutions
//NOTE: Returns a heap allocated string, you are required to free it after use.
char *create_monitor(void)
{
    const unsigned int resolution_numbers[3][2] = {
            {1280, 720},
            {1920, 1080},
            {3840, 2160}
    };
    char *string = NULL;
    cJSON *name = NULL;
    cJSON *resolutions = NULL;
    cJSON *resolution = NULL;
    cJSON *width = NULL;
    cJSON *height = NULL;
    size_t index = 0;

    cJSON *monitor = cJSON_CreateObject();
    if (monitor == NULL)
    {
        goto end;
    }

    name = cJSON_CreateString("Awesome 4K");
    if (name == NULL)
    {
        goto end;
    }
    /* after creation was successful, immediately add it to the monitor,
     * thereby transferring ownership of the pointer to it */
    cJSON_AddItemToObject(monitor, "name", name);

    resolutions = cJSON_CreateArray();
    if (resolutions == NULL)
    {
        goto end;
    }
    cJSON_AddItemToObject(monitor, "resolutions", resolutions);

    for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index)
    {
        resolution = cJSON_CreateObject();
        if (resolution == NULL)
        {
            goto end;
        }
        cJSON_AddItemToArray(resolutions, resolution);

        width = cJSON_CreateNumber(resolution_numbers[index][0]);
        if (width == NULL)
        {
            goto end;
        }
        cJSON_AddItemToObject(resolution, "width", width);

        height = cJSON_CreateNumber(resolution_numbers[index][1]);
        if (height == NULL)
        {
            goto end;
        }
        cJSON_AddItemToObject(resolution, "height", height);
    }

    string = cJSON_Print(monitor);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }

    end:
    cJSON_Delete(monitor);
    return string;
}
int main(int argc, char *argv[]) {
    systemInit();
    run_diagnostics();
    slog_json(create_monitor());
    return 0;
}

