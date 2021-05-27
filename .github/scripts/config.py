import json
from json import JSONEncoder
import globals
from common import *
from downloadBuildArtifact import *
import sys

# subclass JSONEncoder to convert the Config object into JSON
class ConfigEncoder(JSONEncoder):
    def default(self, o):
        return o.__dict__

class Config(object):

    def __init__(self, sha, token, buildArtifactID, workflowRunID, failedWorkflowErrorStr, failedWorkflowReturnCode):
        self.commitSHA = sha                              # Commit SHA for the checkin
        self.accessToken = token                          # Access token for REST APIs
        self.gccBuildArtifactID = buildArtifactID         # GCC Build artifact ID
        self.runID = workflowRunID                        # Run ID of workflow (not job) that ran Setup()
        self.failedWorkflowError = failedWorkflowErrorStr # Whether or not the workflow failed
        self.failedReturnCode = failedWorkflowReturnCode  # Failed workflow error code
        logger = GetLogger()
        logger.info('creating an instance of Config')

    @staticmethod
    def Setup(githubObject, accessToken, isBuild):
        logger = GetLogger()
        
        logger.debug("In Setup")
        logger.debug("---")
        logger.debug("Github object = " + githubObject)
        githubJson = json.loads(githubObject)
        logger.debug(githubJson["event"])
        commit = githubJson["sha"]
        if ("pull_request" in githubJson["event"]):
            commit = githubJson["event"]["pull_request"]["head"]["sha"]

        runID = githubJson["run_id"]
                
        logger.info("SHA = " + commit)
        workflowName = githubJson["workflow"]

        # If this isn't a GCC build, wait for the GCC build to complete with the needed artifacts
        if (not isBuild):
            gccBuildArtifactID = WaitOnGccBuild(commit, accessToken)
        else:
            gccBuildArtifactID = 0

        # Construct Config object
        newConfig = Config(commit, accessToken, gccBuildArtifactID, runID, '', 0)
        configJson = json.dumps(newConfig, cls=ConfigEncoder)

        # Output for Github to pick up output for future steps
        print("::set-output name=configJson::" + configJson)

        # Set global config object
        globals.configObj = newConfig

    @staticmethod
    def PrintNoSecretConfigJson():
        # GitHub won't allow the printing of strings with secrets in them for future jobs
        # so we need to clear out any secrets in our config object prior to printing it

        # Clear out the access token field
        globals.configObj.accessToken = globals.configObj.accessToken.replace(globals.configObj.accessToken, '')
        configJson = json.dumps(globals.configObj, cls=ConfigEncoder)

        # Output for Github to pick up output for future jobs
        print("::set-output name=noSecretConfigJson::" + configJson)

    @staticmethod
    def PrintNoSecretConfigJsonFromJson(configJson):
        Config.Reload(configJson)
        Config.PrintNoSecretConfigJson()

    @staticmethod
    def Reload(configJson, accessToken=""):
        loadedJson = json.loads(configJson)
        
        # If no access token is provided, use the one in the config already
        # This is possible in cases where the config setup and reload functions are run on the same machine
        if (accessToken==""):
            accessToken=loadedJson["accessToken"]

        # Set global config object
        globals.configObj = Config(loadedJson["commitSHA"], accessToken, loadedJson["gccBuildArtifactID"], loadedJson["runID"], loadedJson["failedWorkflowError"], loadedJson["failedReturnCode"])
        
    @staticmethod
    def RaiseErrorIfWorkflowFailed():
        if (globals.configObj.failedWorkflowError):
            logger = GetLogger()
            logger.error(globals.configObj.failedWorkflowError)
            logging.shutdown()
            sys.exit(globals.configObj.failedReturnCode)
