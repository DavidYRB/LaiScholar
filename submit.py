from optparse import OptionParser
import tarfile
import json
import tempfile
import os
import requests

CONFIG_FILE = './submission.json'
SUBMISSION_SERVER = 'https://cpp-in-production.appspot.com'
SUBMISSION_PATH = 'submit'

def main():
    parser = OptionParser()
    parser.add_option('-p', '--project', dest='project', default='',
            help='specify the project, which will override the one in config file.')
    (options, args) = parser.parse_args()

    print('Loading config...')
    with open(CONFIG_FILE, 'r') as f:
        config = json.load(f)

    email = config['email']
    project = config['project']
    if len(options.project) > 0:
        project = options.project

    print('Submitting for:')
    print('Email: {}'.format(email))
    print('Project: {}'.format(project))

    output_file, output_filename = tempfile.mkstemp(suffix='.tar.gz')
    with os.fdopen(output_file, 'wb') as output_file:
        artifact = tarfile.open(fileobj=output_file, mode='w:gz')
        for fn in config['files']:
            artifact.add(fn)
        artifact.close()

    data = {
        'email': email,
        'project': project,
    }
    with open(output_filename, 'rb') as f:
        files = {
            'submission': f,
        }
        resp = requests.post('{}/{}'.format(SUBMISSION_SERVER, SUBMISSION_PATH), data=data, files=files)

    if not resp.ok:
        print('ERROR: {}.'.format(resp.json()['message']))
    else:
        print('Successfully submitted!\nGo to check the status at: {}'.format(resp.json()['status_url']))

    os.remove(output_filename)


if __name__ == '__main__':
    main()
