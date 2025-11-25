#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CROP_TYPE 20
#define MAX_WEATHER 10
#define MAX_FARM_ID 10

// Node structure for singly linked list
typedef struct FarmNode {
    char farmId[MAX_FARM_ID];
    char cropType[MAX_CROP_TYPE];
    float soilMoisture;
    float moistureThreshold;
    char weatherForecast[MAX_WEATHER];
    int needsIrrigation; // 1 if irrigation needed, 0 otherwise
    struct FarmNode* next;
} FarmNode;

// Global pointer to head of linked list
FarmNode* head = NULL;

// Function prototypes
void insertFarm();
void deleteFarm();
void displayFarms();
void searchFarm();
void checkIrrigation();
void freeList();
int isValidFarmId(const char* id);
float getThresholdByCrop(const char* cropType);
void toLower(char* s);
void printMenu();

// Main function
int main() {
    int choice;

    printf("=== Farm Irrigation Scheduler ===\n");
    printf("Using Singly Linked Lists for Dynamic Management\n\n");

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                insertFarm();
                break;
            case 2:
                deleteFarm();
                break;
            case 3:
                displayFarms();
                break;
            case 4:
                searchFarm();
                break;
            case 5:
                checkIrrigation();
                break;

            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 6);

    freeList();
    return 0;
}

void printMenu() {
    printf("\n=== MENU ===\n");
    printf("1. Insert New Farm\n");
    printf("2. Delete Farm by ID\n");
    printf("3. Display All Farms\n");
    printf("4. Search Farm by ID\n");
    printf("5. Check Irrigation Needs\n");
    printf("6. Exit\n");
}

// Convert string to lowercase
void toLower(char* s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower(s[i]);
}

// Insert new farm at the end of linked list
void insertFarm() {
    FarmNode* newNode = (FarmNode*)malloc(sizeof(FarmNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("\n--- Insert New Farm ---\n");

    // Get farm ID with validation + prevent overflow
    do {
        printf("Enter Farm ID (alphanumeric, max 9 chars): ");
        scanf("%9s", newNode->farmId);
    } while(!isValidFarmId(newNode->farmId));

    // Check if farm ID already exists
    FarmNode* current = head;
    while (current != NULL) {
        if (strcmp(current->farmId, newNode->farmId) == 0) {
            printf("Error: Farm ID already exists!\n");
            free(newNode);
            return;
        }
        current = current->next;
    }

    printf("Enter Crop Type: ");
    scanf("%19s", newNode->cropType);

    printf("Enter Current Soil Moisture (%%): ");
    scanf("%f", &newNode->soilMoisture);

    printf("Enter Weather Forecast (Sunny/Rain/Cloudy): ");
    scanf("%9s", newNode->weatherForecast);

    // Case-insensitive handling
    char cropLower[MAX_CROP_TYPE];
    strcpy(cropLower, newNode->cropType);
    toLower(cropLower);

    newNode->moistureThreshold = getThresholdByCrop(cropLower);
    newNode->needsIrrigation = 0;
    newNode->next = NULL;

    // Insert at the end of linked list
    if (head == NULL) {
        head = newNode;
    } else {
        current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    printf("Farm '%s' added successfully!\n", newNode->farmId);
}

// Delete farm by ID from linked list
void deleteFarm() {
    if (head == NULL) {
        printf("No farms in the system!\n");
        return;
    }

    char id[MAX_FARM_ID];
    printf("Enter Farm ID to delete: ");
    scanf("%9s", id);

    FarmNode* current = head;
    FarmNode* prev = NULL;

    // Search for the node to delete
    while (current != NULL && strcmp(current->farmId, id) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Farm with ID '%s' not found!\n", id);
        return;
    }

    // Delete the node
    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    printf("Farm '%s' deleted successfully!\n", current->farmId);
    free(current);
}

// Display all farms in the linked list

void displayFarms() {
    if (head == NULL) {
        printf("No farms in the system!\n");
        return;
    }

    printf("\n--- All Farms ---\n");
    printf("%-10s %-15s %-13s %-11s %-10s %s\n",
           "Farm ID", "Crop Type", "Moisture", "Threshold", "Weather", "Irrigation");
    printf("------------------------------------------------------------------------\n");

    FarmNode* current = head;
    while (current != NULL) {
        printf("%-10s %-15s %-11.1f%% %-9.1f%% %-10s %s\n",
               current->farmId,
               current->cropType,
               current->soilMoisture,
               current->moistureThreshold,
               current->weatherForecast,
               current->needsIrrigation ? "NEEDED" : "Not Needed");
        current = current->next;
    }
}

// Linear search to find farm by ID
void searchFarm() {
    if (head == NULL) {
        printf("No farms in the system!\n");
        return;
    }

    char id[MAX_FARM_ID];
    printf("Enter Farm ID to search: ");
    scanf("%9s", id);

    FarmNode* current = head;
    while (current != NULL) {
        if (strcmp(current->farmId, id) == 0) {
            printf("\n--- Farm Found ---\n");
            printf("Farm ID: %s\n", current->farmId);
            printf("Crop Type: %s\n", current->cropType);
            printf("Soil Moisture: %.1f%%\n", current->soilMoisture);
            printf("Moisture Threshold: %.1f%%\n", current->moistureThreshold);
            printf("Weather Forecast: %s\n", current->weatherForecast);
            printf("Irrigation Needed: %s\n",
                   current->needsIrrigation ? "YES" : "NO");
            return;
        }
        current = current->next;
    }

    printf("Farm with ID '%s' not found!\n", id);
}

// Check irrigation needs by traversing linked list
void checkIrrigation() {
    if (head == NULL) {
        printf("No farms in the system!\n");
        return;
    }

    printf("\n--- Irrigation Check ---\n");
    int irrigationCount = 0;

    FarmNode* current = head;
    while (current != NULL) {

        char weatherLower[MAX_WEATHER];
        strcpy(weatherLower, current->weatherForecast);
        toLower(weatherLower);

        if (current->soilMoisture < current->moistureThreshold &&
            strcmp(weatherLower, "rain") != 0) {

            current->needsIrrigation = 1;
            irrigationCount++;
            printf("✓ Farm '%s' (%s) needs irrigation! (Moisture: %.1f%%, Threshold: %.1f%%)\n",
                   current->farmId, current->cropType, current->soilMoisture, current->moistureThreshold);
        } else {
            current->needsIrrigation = 0;
            printf("  Farm '%s' (%s) - No irrigation needed\n",
                   current->farmId, current->cropType);
        }
        current = current->next;
    }

    printf("\nTotal farms needing irrigation: %d\n", irrigationCount);
}

// Free all nodes in the linked list
void freeList() {
    FarmNode* current = head;
    while (current != NULL) {
        FarmNode* next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

// Validate farm ID (alphanumeric)
int isValidFarmId(const char* id) {
    if (strlen(id) == 0 || strlen(id) >= MAX_FARM_ID) {
        printf("Farm ID must be 1-9 characters long!\n");
        return 0;
    }

    for (int i = 0; id[i] != '\0'; i++) {
        if (!isalnum(id[i])) {
            printf("Farm ID must contain only letters and numbers!\n");
            return 0;
        }
    }
    return 1;
}

// Get moisture threshold based on crop type (case-insensitive)
float getThresholdByCrop(const char* cropLower) {
    if (strcmp(cropLower, "wheat") == 0) return 40.0;
    if (strcmp(cropLower, "corn") == 0) return 45.0;
    if (strcmp(cropLower, "rice") == 0) return 60.0;
    if (strcmp(cropLower, "soybean") == 0) return 35.0;
    if (strcmp(cropLower, "cotton") == 0) return 30.0;
    if (strcmp(cropLower, "tomato") == 0) return 50.0;
    if (strcmp(cropLower, "potato") == 0) return 55.0;

    return 40.0; // Default threshold
}
